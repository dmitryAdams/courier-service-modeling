//
// Created by adams on 10/6/24.
//

#ifndef COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_
#define COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_

#include "QMainWindow"

class MainDispetcherWindow : public QMainWindow{
  Q_OBJECT
 public:
  MainDispetcherWindow(int office_counter, int branch_counter, std::vector<std::vector<int>> maxtrix, QWidget *parent = nullptr);
};

#endif //COURIER_SERVICE_MODELING_FRONTEND_MAINDISPETCHERWINDOW_MAINDISPETCHERWINDOW_H_
