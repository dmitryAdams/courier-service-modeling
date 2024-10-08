//
// Created by adams on 10/6/24.
//

#include "MainDispetcherWindow.h"
#include "QApplication"
#include "QScreen"
#include "iostream"
#include "QMessageBox"

MainDispetcherWindow::MainDispetcherWindow(QWidget *parent) :
    QWidget(parent),
    logs_(new QTextBrowser()),
    set_company_size_button_(new QPushButton()),
    set_average_time_button_(new QPushButton()),
    set_offices_priority_button_(new QPushButton()),
    start_button_(new QPushButton()),
    main_layout_(new QGridLayout(this)),
    button_layout_(new QBoxLayout(QBoxLayout::LeftToRight)),
    office_counter_(-1),
    courier_counter_(-1),
    company_size_window_(new CompanySetSizeWindow(this)),
    set_time_window_(new SetTimeWindow(0, 0, this)),
    office_priority_window_(new OfficePriorityWindow(0, this)) {

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

  QLabel *map_label = new QLabel(this);

  main_layout_->addWidget(map_label, 0, 0);
  main_layout_->addWidget(logs_, 0, 1);
  main_layout_->addLayout(button_layout_, 1, 0, 1, 2);

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
  show();
  auto screen_size = QApplication::screens()[0]->size();
  setGeometry(0, 0, screen_size.width(), screen_size.height());
}

void MainDispetcherWindow::set_company_size_button_clicked_() {
  company_size_window_->show();
}

void MainDispetcherWindow::set_average_time_button_clicked_() {
  if (office_counter_ != -1) {
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
  if (office_counter_ != -1) {
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

}

void MainDispetcherWindow::change_company_size() {
  office_counter_ = company_size_window_->office_count();
  courier_counter_ = company_size_window_->courier_count();

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
}
void MainDispetcherWindow::change_office_priority(const std::vector<int> &priority) {
  priority_ = priority;
}
