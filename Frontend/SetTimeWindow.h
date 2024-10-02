//
// Created by adams on 10/2/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_SETTIMEWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_SETTIMEWINDOW_H_

#include "QMainWindow"
#include "QTableWidget"

class SetTimeWindow : public QMainWindow {
 Q_OBJECT
 public:
  SetTimeWindow(int office_count, int courier_count, QWidget *parent = nullptr);
 private:
  QTableWidget *table_widget_;
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_SETTIMEWINDOW_H_
