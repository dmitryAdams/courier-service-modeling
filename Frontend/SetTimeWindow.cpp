//
// Created by adams on 10/2/24.
//

#include "SetTimeWindow.h"

SetTimeWindow::SetTimeWindow(int office_count, int courier_count, QWidget *parent) :
    QMainWindow(parent),
    table_widget_(new QTableWidget(this)) {
  setGeometry(0, 0, 700, 700);
  table_widget_->setColumnCount(2);
  table_widget_->setRowCount(office_count * (office_count - 1) / 2);
  table_widget_->setGeometry(0, 0, 700, 700);
  int cnt = 0;
  for (int i = 1; i <= office_count; ++i) {
    for (int j = i + 1; j <= office_count; ++j) {
      table_widget_->setItem(cnt++,
                             0,
                             new QTableWidgetItem(QString::number(i) + " - " + QString::number(j)));
    }
  }
}
