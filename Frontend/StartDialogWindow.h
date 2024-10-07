//
// Created by adams on 10/2/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_STARTDIALOGWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_STARTDIALOGWINDOW_H_

#include "QMainWindow"
#include "QLineEdit"
#include "QPushButton"
#include "QDialog"

class StartDialogWindow : public QDialog {
 Q_OBJECT
 public:
  StartDialogWindow(QWidget *parent = nullptr);
 private:
  QLineEdit *branch_line_edit_, *courier_line_edit_;
  QPushButton *accept_button;
 private slots:
  void accept_button_clicked();
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_STARTDIALOGWINDOW_H_
