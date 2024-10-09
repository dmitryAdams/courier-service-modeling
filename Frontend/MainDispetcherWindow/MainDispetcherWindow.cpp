//
// Created by adams on 10/6/24.
//

#include <iostream>
#include <numeric>
#include "MainDispetcherWindow.h"
#include "QApplication"
#include "QScreen"
#include "QMessageBox"
#include "math.h"
#include "QPropertyAnimation"
#include "QVector2D"
#include "../../Time/Time.h"

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
    dispetcher_service_(nullptr),
    timer_(new QTimer(this)),
    map_label_(new QLabel), office_sprite_size_(100),
    center_of_offices_(400, 270),
    radius_(270),
    debug_cnt_(0),
    minutes_per_step(1),
    time_for_animation_(10) {

  timer_->setInterval(30);

  set_company_size_button_->setText("Задать размер компании");
  set_average_time_button_->setText("Задать среднее расстояние");
  set_offices_priority_button_->setText("Задать \"размеры\" офисов");
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
    if (timer_->isActive()) {
      start_button_->setText("Start");
      timer_->stop();
    } else {
      delete dispetcher_service_;
      dispetcher_service_ = new Service(office_counter_, courier_counter_, matrix_);
      auto couriers = dispetcher_service_->getCouriers();
      for (int i = 0; i < courier_counter_; ++i) {
        prev_from_for_courier_[i] = couriers[i]->comingFrom();
      }
      timer_->start();
      start_button_->setText("Stop");
    }
  } else {
    QMessageBox::critical(this, "Ошбика", "Ой, кажется вы не задали размеры компании");
  }
}

void MainDispetcherWindow::change_company_size() {
  logs_->clear();
  QPixmap office_pixmap("../sprites/office.png");
  QPixmap courier_pixmap("../sprites/courier.png");
  if (office_counter_ < company_size_window_->office_count()) {
    office_sprites_labels_list_.resize(company_size_window_->office_count());
    double angle = M_PI * 2 / company_size_window_->office_count();
    for (int i = office_counter_; i < office_sprites_labels_list_.size(); ++i) {
      office_sprites_labels_list_[i] = new QLabel(map_label_);
      office_sprites_labels_list_[i]->setGeometry(center_of_offices_.x(),
                                                  center_of_offices_.y(),
                                                  office_sprite_size_,
                                                  office_sprite_size_);
      office_sprites_labels_list_[i]->setPixmap(office_pixmap.scaled(office_sprite_size_,
                                                                     office_sprite_size_,
                                                                     Qt::KeepAspectRatio));
      office_sprites_labels_list_[i]->show();
    }
    for (int i = 0; i < office_sprites_labels_list_.size(); ++i) {
      QPropertyAnimation *animation = new QPropertyAnimation(office_sprites_labels_list_[i], "geometry");
      animation->setDuration(500);
      animation->setEasingCurve(QEasingCurve::Linear);
      animation->setEndValue(QRectF(std::cos(angle * i) * radius_ + center_of_offices_.x(),
                                    std::sin(angle * i) * radius_ + center_of_offices_.y(),
                                    office_sprite_size_,
                                    office_sprite_size_));
      animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
  } else {
    for (int i = office_counter_ - 1; i >= company_size_window_->office_count(); --i) {
      delete office_sprites_labels_list_[i];
    }
    office_sprites_labels_list_.resize(company_size_window_->office_count());
    double angle = M_PI * 2 / company_size_window_->office_count();
    for (int i = 0; i < office_sprites_labels_list_.size(); ++i) {
      QPropertyAnimation *animation = new QPropertyAnimation(office_sprites_labels_list_[i], "geometry");
      animation->setDuration(500);
      animation->setEasingCurve(QEasingCurve::Linear);
      animation->setEndValue(QRectF(std::cos(angle * i) * radius_ + center_of_offices_.x(),
                                    std::sin(angle * i) * radius_ + center_of_offices_.y(),
                                    office_sprite_size_,
                                    office_sprite_size_));
      animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
  }

  if (courier_counter_ < company_size_window_->courier_count()) {
    courier_sprites_labels_list_.resize(company_size_window_->courier_count());
    for (int i = courier_counter_; i < courier_sprites_labels_list_.size(); ++i) {
      courier_sprites_labels_list_[i] = new QLabel(map_label_);
      courier_sprites_labels_list_[i]->setPixmap(courier_pixmap.scaled(office_sprite_size_ * 0.66,
                                                                       office_sprite_size_ * 0.66,
                                                                       Qt::KeepAspectRatio));
      courier_sprites_labels_list_[i]->setGeometry(-1000, -1000, office_sprite_size_ * 0.66, office_sprite_size_ * 0.66);
      courier_sprites_labels_list_[i]->show();
    }
  } else {
    for (int i = courier_counter_ - 1; i >= courier_sprites_labels_list_.size(); --i) {
      delete courier_sprites_labels_list_[i];
    }
    courier_sprites_labels_list_.resize(company_size_window_->courier_count());
  }
  office_counter_ = company_size_window_->office_count();
  courier_counter_ = company_size_window_->courier_count();

  prev_from_for_courier_.resize(courier_counter_);

  matrix_.assign(office_counter_ + 1, std::vector<int>(office_counter_ + 1, 60));
  priority_.assign(office_counter_, -1);

  delete set_time_window_;
  set_time_window_ = new SetTimeWindow(office_counter_, courier_counter_, this);

  delete office_priority_window_;
  office_priority_window_ = new OfficePriorityWindow(office_counter_, this);
}

void MainDispetcherWindow::change_office_distance(const std::vector<std::vector<int>> &matrix) {
  matrix_.resize(matrix.size() + 1, std::vector<int>(matrix.size() + 1));
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      matrix_[i + 1][j + 1] = matrix[i][j];
    }
  }
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
  for (auto i : office_sprites_labels_list_) delete i;
}
void MainDispetcherWindow::change_office_priority(const std::vector<int> &priority) {
  priority_ = priority;
}
void MainDispetcherWindow::make_step() {
  auto log_messages = dispetcher_service_->nextStep(minutes_per_step);
  auto couriers = dispetcher_service_->getCouriers();
  for (int i = 0; i < couriers.size(); ++i) {
    auto courier = couriers[i];
    if (courier->isOnTheWay()) {
      if (prev_from_for_courier_[i] != courier->comingFrom()) {
        QPropertyAnimation *animation = new QPropertyAnimation(courier_sprites_labels_list_[i], "geometry");
        animation->setDuration(time_for_animation_);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->setEndValue(QRectF(office_sprites_labels_list_[courier->comingFrom() - 1]->x(),
                                      office_sprites_labels_list_[courier->comingFrom() - 1]->y(),
                                      courier_sprites_labels_list_[i]->width(),
                                      courier_sprites_labels_list_[i]->height()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        prev_from_for_courier_[i] = courier->comingFrom();
      } else {
        ++debug_cnt_;
        QVector2D vec(office_sprites_labels_list_[courier->goingTo() - 1]->pos().x()
                          - office_sprites_labels_list_[courier->comingFrom() - 1]->x(),
                      office_sprites_labels_list_[courier->goingTo() - 1]->pos().y()
                          - office_sprites_labels_list_[courier->comingFrom() - 1]->y());
        vec *= std::min(1.0, minutes_per_step * 1.0 / matrix_[courier->comingFrom()][courier->goingTo()]);
        QPropertyAnimation *animation = new QPropertyAnimation(courier_sprites_labels_list_[i], "geometry");
        animation->setDuration(time_for_animation_);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->setEndValue(QRectF(courier_sprites_labels_list_[i]->x() + vec.x(),
                                      courier_sprites_labels_list_[i]->y() + vec.y(),
                                      courier_sprites_labels_list_[i]->width(),
                                      courier_sprites_labels_list_[i]->height()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
      }
    } else {
      QPropertyAnimation *animation = new QPropertyAnimation(courier_sprites_labels_list_[i], "geometry");
      animation->setDuration(time_for_animation_);
      animation->setEasingCurve(QEasingCurve::Linear);
      animation->setEndValue(QRectF(office_sprites_labels_list_[courier->comingFrom() - 1]->x(),
                                    office_sprites_labels_list_[courier->comingFrom() - 1]->y(),
                                    courier_sprites_labels_list_[i]->width(),
                                    courier_sprites_labels_list_[i]->height()));
      animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
  }
  for (auto message : log_messages) {
    if (message.isOut) {
      logs_->append(
          "Курьер #" + QString::number(message.courierId) + " вышел из офиса#" + QString::number(message.branchId)
              + " в " +
              QString::fromStdString(Time(message.time).getStringTime()));
    } else {
      logs_->append(
          "Курьер #" + QString::number(message.courierId) + " пришел в офис #" + QString::number(message.branchId)
              + " в " +
              QString::fromStdString(Time(message.time).getStringTime()));
    }
  }
}
