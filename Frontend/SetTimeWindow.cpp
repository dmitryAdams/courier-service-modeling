//
// Created by adams on 10/2/24.
//

#include "SetTimeWindow.h"
#include "iostream"

SetTimeWindow::SetTimeWindow(int office_count, int courier_count, QWidget *parent) :
    QMainWindow(parent),
    table_widget_(new QTableWidget(this)),
    accept_button_(new QPushButton(this)) {
  const int row_count = office_count * (office_count - 1) / 2;
  setGeometry(0, 0, 140, 110 + 600 * row_count / 21);
  table_widget_->setColumnCount(1);
  table_widget_->setRowCount(row_count);
  table_widget_->setGeometry(0, 0, 140, 700);
  QStringList qsl;
  for (int i = 1; i <= office_count; ++i) {
    for (int j = i + 1; j <= office_count; ++j) {
      qsl << (QString::number(i) + " - " + QString::number(j));
    }
  }
  table_widget_->setVerticalHeaderLabels(qsl);
  qsl.clear();
  qsl << "Время в пути:";
  table_widget_->setHorizontalHeaderLabels(qsl);

  accept_button_->setGeometry(0, 60 + 600 * row_count / 21, 140, 50);
  accept_button_->setText("Задать");
  connect(accept_button_, &QPushButton::clicked, this, &SetTimeWindow::accept_button_clicked);
}
void SetTimeWindow::accept_button_clicked() {

}
