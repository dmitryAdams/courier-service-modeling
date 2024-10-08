//
// Created by adams on 10/6/24.
//

#include <iostream>
#include "MainDispetcherWindow.h"
#include "QApplication"
#include "QScreen"
#include "QMessageBox"
#include "math.h"
#include "QPropertyAnimation"

MainDispetcherWindow::MainDispetcherWindow(QWidget *parent) :
    QWidget(parent),
    logs_(new QTextBrowser()),
    set_company_size_button_(new QPushButton),
    set_average_time_button_(new QPushButton),
    set_offices_priority_button_(new QPushButton()),
    start_button_(new QPushButton()),
    main_layout_(new QGridLayout(this)),
    button_layout_(new QBoxLayout(QBoxLayout::LeftToRight)),
    office_counter_(0),
    courier_counter_(0),
    company_size_window_(new CompanySetSizeWindow(this)),
    set_time_window_(new SetTimeWindow(0, 0, this)),
    office_priority_window_(new OfficePriorityWindow(0, this)),
    dispetcher_service_(new Service(0, 0, {})),
    timer_(new QTimer(this)),
    map_label_(new QLabel), office_sprite_size_(100),
    center_of_offices_(400, 400),
    radius_(500) {

  timer_->setInterval(1000);

  set_company_size_button_->setText("company");
  set_average_time_button_->setText("average");
  set_offices_priority_button_->setText("priority");
  start_button_->setText("start");

  const int mnHeight = 50;
  logs_->setMaximumWidth(300);
  set_company_size_button_->setMinimumHeight(mnHeight);
  set_average_time_button_->setMinimumHeight(mnHeight);
  set_offices_priority_button_->setMinimumHeight(mnHeight);
  start_button_->setMinimumHeight(mnHeight);

  button_layout_->insertWidget(0, set_company_size_button_);
  button_layout_->insertWidget(1, set_average_time_button_);
  button_layout_->insertWidget(2, set_offices_priority_button_);
  button_layout_->insertWidget(3, start_button_);

  main_layout_->addWidget(map_label_, 0, 0);
  main_layout_->addWidget(logs_, 0, 1);
  main_layout_->addLayout(button_layout_, 1, 0, 1, 2);

  map_label_->setMinimumSize(1000, 600);
  QPixmap map("../sprites/map2.jpg");
  map_label_->setPixmap(map.scaled(1005, 1e9, Qt::KeepAspectRatio));
  std::cerr << map_label_->height();

  connect(set_company_size_button_,
          &QPushButton::clicked,
          this,
          &MainDispetcherWindow::set_company_size_button_clicked_);
  connect(set_average_time_button_,
          &QPushButton::clicked,
          this,
          &MainDispetcherWindow::set_average_time_button_clicked_);
  connect(set_offices_priority_button_,
          &QPushButton::clicked,
          this,
          &MainDispetcherWindow::set_offices_priority_button_clicked_);
  connect(start_button_,
          &QPushButton::clicked,
          this,
          &MainDispetcherWindow::start_button_clicked_);
  connect(company_size_window_,
          &CompanySetSizeWindow::data_entered_correctly,
          this,
          &MainDispetcherWindow::change_company_size);
  connect(timer_, &QTimer::timeout, this, &MainDispetcherWindow::make_step);

  auto screen_size = QApplication::screens()[0]->size();
  setGeometry(0, 0, screen_size.width(), screen_size.height());
}

void MainDispetcherWindow::set_company_size_button_clicked_() {
  company_size_window_->show();
}

void MainDispetcherWindow::set_average_time_button_clicked_() {
  if (office_counter_ != 0) {
    connect(set_time_window_,
            &SetTimeWindow::data_entered_correctly,
            this,
            &MainDispetcherWindow::change_office_distance);
    set_time_window_->show();
  } else {
    QMessageBox::critical(this, "Ошбика", "Ой, кажется вы не задали размеры компании");
  }
}

void MainDispetcherWindow::set_offices_priority_button_clicked_() {
  if (office_counter_ != 0) {
    connect(office_priority_window_,
            &OfficePriorityWindow::data_entered_correctly,
            this,
            &MainDispetcherWindow::change_office_priority);
    office_priority_window_->show();
  } else {
    QMessageBox::critical(this, "Ошбика", "Ой, кажется вы не задали размеры компании");
  }
}

void MainDispetcherWindow::start_button_clicked_() {
  if (office_counter_ != 0) {
    delete dispetcher_service_;
    dispetcher_service_ = new Service(office_counter_, courier_counter_, matrix_);
    timer_->start();
  } else {
    QMessageBox::critical(this, "Ошбика", "Ой, кажется вы не задали размеры компании");
  }
}

void MainDispetcherWindow::change_company_size() {
  if (office_counter_ < company_size_window_->office_count()) {
    office_sprites_labels_list_.resize(office_counter_);
    QPixmap office_pixmap("../sprites/office.png");
    double angle = M_PI * 2 / company_size_window_->office_count();
    for (int i = office_counter_; i < office_sprites_labels_list_.size(); ++i) {
      office_sprites_labels_list_[i] = new QLabel(map_label_);
      office_sprites_labels_list_[i]->setGeometry(30, 30, 40, 40);
      office_sprites_labels_list_[i]->setPixmap(office_pixmap.scaled(40, 40, Qt::KeepAspectRatio));
      office_sprites_labels_list_[i]->show();
    }
//    for (int i = 0; i < office_sprites_labels_list_.size(); ++i) {
//      QPropertyAnimation *animation = new QPropertyAnimation(office_sprites_labels_list_[i], "geometry");
//      animation->setDuration(500);
//      animation->setEasingCurve(QEasingCurve::Linear);
//      animation->setEndValue(QRectF(std::cos(angle * i) * radius_ + center_of_offices_.x(),
//                                    std::sin(angle * i) * radius_ + center_of_offices_.y(),
//                                    office_sprites_labels_list_[i]->width(),
//                                    office_sprites_labels_list_[i]->height()));
//      animation->start(QAbstractAnimation::DeleteWhenStopped);
//    }
  } else {
    office_sprites_labels_list_.resize(office_counter_);
    QPixmap office_pixmap("../sprites/office.png");
    for (int i = 0; i < office_counter_; ++i) {
      QLabel *cur_office_label = new QLabel(map_label_);
      cur_office_label->setMaximumSize(40, 40);
      cur_office_label->setGeometry(30, 30, 40, 40);
      cur_office_label->setPixmap(office_pixmap.scaled(40, 40, Qt::KeepAspectRatio));
      cur_office_label->show();
    }
  }
  office_counter_ = company_size_window_->office_count();
  courier_counter_ = company_size_window_->courier_count();

  matrix_.assign(office_counter_, std::vector<int>(office_counter_, -1));
  priority_.assign(office_counter_, -1);

  delete set_time_window_;
  set_time_window_ = new SetTimeWindow(office_counter_, courier_counter_, this);

  delete office_priority_window_;
  office_priority_window_ = new OfficePriorityWindow(office_counter_, this);
}

void MainDispetcherWindow::change_office_distance(const std::vector<std::vector<int>> &matrix) {
  matrix_ = matrix;
}

MainDispetcherWindow::~MainDispetcherWindow() {
  delete logs_;
  delete set_company_size_button_;
  delete set_offices_priority_button_;
  delete set_average_time_button_;
  delete start_button_;
  delete set_time_window_;
  delete company_size_window_;
  delete dispetcher_service_;
  delete timer_;
  delete map_label_;
}
void MainDispetcherWindow::change_office_priority(const std::vector<int> &priority) {
  priority_ = priority;
}
void MainDispetcherWindow::make_step() {
  dispetcher_service_->nextStep(30);
}
