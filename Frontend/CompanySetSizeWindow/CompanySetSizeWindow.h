//
// Created by adams on 10/2/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_COMPANYSETSIZEWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_COMPANYSETSIZEWINDOW_H_

#include "QMainWindow"
#include "QLineEdit"
#include "QPushButton"
#include "QDialog"

class CompanySetSizeWindow : public QDialog {
 Q_OBJECT
 public:
  CompanySetSizeWindow(QWidget *parent = nullptr);
 ~CompanySetSizeWindow();
  int office_count();
  int courier_count();
 private:
  QLineEdit *office_line_edit_, *courier_line_edit_;
  QPushButton *accept_button_;
 signals:
  void data_entered_correctly();
 private slots:
  void accept_button_clicked();
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_COMPANYSETSIZEWINDOW_H_
