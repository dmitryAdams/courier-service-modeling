//
// Created by adams on 10/2/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_SETTIMEWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_SETTIMEWINDOW_H_

#include "QMainWindow"
#include "QTableWidget"
#include "QPushButton"
#include "QDialog"

class SetTimeWindow : public QDialog {
 Q_OBJECT
 public:
  SetTimeWindow(int office_count, int courier_count, QWidget *parent = nullptr);
 ~SetTimeWindow() override;
 private:
  QTableWidget *table_of_average_distance_;
  QPushButton *accept_button_;
  int office_counter_, courier_counter_;
 signals:
  void data_entered_correctly(const std::vector<std::vector<int>> &matrix);
 private slots:
  void accept_button_clicked();
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_SETTIMEWINDOW_H_
