//
// Created by adams on 10/7/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_OFFICEPRIORITYWINDOW_OFFICEPRIORITYWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_OFFICEPRIORITYWINDOW_OFFICEPRIORITYWINDOW_H_
#include "QDialog"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "vector"
#include "QLineEdit"
#include "QPushButton"

class OfficePriorityWindow : public QDialog {
  Q_OBJECT
 public:
  OfficePriorityWindow(int office_counter, QWidget *parent = nullptr);
 private:
  QVBoxLayout *main_layout_;
  QHBoxLayout *line_edits_layout_;
  QPushButton *accept_button_;
  std::vector<QLineEdit *> priorities_line_edits_;
 signals:
  void data_entered_correctly(const std::vector<int> &);
 private slots:
  void accept_button_clicked_();
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_OFFICEPRIORITYWINDOW_OFFICEPRIORITYWINDOW_H_
