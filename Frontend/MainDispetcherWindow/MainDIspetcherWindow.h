//
// Created by adams on 10/6/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_

#include "QMainWindow"
#include "QTextBrowser"
#include "QPushButton"
#include "QGridLayout"
#include "QBoxLayout"
#include "QLabel"
#include "../StartDialogWindow.h"

class MainDispetcherWindow : public QWidget {
 Q_OBJECT
 public:
  MainDispetcherWindow(QWidget *parent = nullptr);
 private slots:
  void set_company_size_button_clicked_();
  void set_average_time_button_clicked_();
  void set_offices_priority_button_clicked_();
  void start_button_clicked_();
  void change_company_size();
 private:
  StartDialogWindow *company_size_window_;
  QTextBrowser *logs_;
  QPushButton *set_company_size_button_,
      *set_average_time_button_,
      *set_offices_priority_button_,
      *start_button_;
  int office_counter_, courier_counter_;
  QGridLayout *main_layout_;
  QBoxLayout *button_layout_;
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_
