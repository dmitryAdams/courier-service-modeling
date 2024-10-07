//
// Created by adams on 10/6/24.
//

#include "MainDIspetcherWindow.h"
#include "QApplication"
#include "QScreen"
#include "iostream"

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
    company_size_window_(new StartDialogWindow(this)) {

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
          &StartDialogWindow::data_entered_correctly,
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

}
void MainDispetcherWindow::set_offices_priority_button_clicked_() {

}
void MainDispetcherWindow::start_button_clicked_() {

}
void MainDispetcherWindow::change_company_size() {
  office_counter_ = company_size_window_->office_count();
  courier_counter_ = company_size_window_->courier_count();
  std::cerr << office_counter_ << ' ' << courier_counter_ << '\n';
}
