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
#include "../CompanySetSizeWindow/CompanySetSizeWindow.h"
#include "../SetTimeWindow/SetTimeWindow.h"
#include "../OfficePriorityWindow/OfficePriorityWindow.h"
#include "../../service/Service.h"
#include "QTimer"
#include "QPixmap"

class MainDispetcherWindow : public QWidget {
 Q_OBJECT
 public:
  MainDispetcherWindow(QWidget *parent = nullptr);
  ~MainDispetcherWindow();
 private slots:
  void set_company_size_button_clicked_();
  void set_average_time_button_clicked_();
  void set_offices_priority_button_clicked_();
  void start_button_clicked_();
  void change_company_size();
  void change_office_distance(const std::vector<std::vector<int>> &matrix);
  void change_office_priority(const std::vector<int> &priority);
  void make_step();
 private:
  int office_sprite_size_;
  CompanySetSizeWindow *company_size_window_;
  SetTimeWindow *set_time_window_;
  OfficePriorityWindow *office_priority_window_;
  QTextBrowser *logs_;
  QPushButton *set_company_size_button_,
      *set_average_time_button_,
      *set_offices_priority_button_,
      *start_button_;
  int office_counter_, courier_counter_;
  QGridLayout *main_layout_;
  QBoxLayout *button_layout_;
  std::vector<std::vector<int>> matrix_;
  std::vector<int> priority_;
  bool company_size_was_updated_;
  Service *dispetcher_service_;
  QTimer *timer_;
  QLabel *map_label_;
  QPoint center_of_offices_;
  int radius_;
  std::vector<QLabel *> office_sprites_labels_list_;
  std::vector<QLabel *> courier_sprites_labels_list_;
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_
