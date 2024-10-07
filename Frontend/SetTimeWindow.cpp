//
// Created by adams on 10/2/24.
//

#include "SetTimeWindow.h"
#include "iostream"
#include "QMessageBox"
#include "../Time/Time.h"
#include "QLineEdit"
#include "QFormLayout"
#include "QLabel"
#include "./MainDispetcherWindow/MainDIspetcherWindow.h"

SetTimeWindow::SetTimeWindow(int office_count, int courier_count, QWidget *parent) :
    QDialog(parent),
    table_widget_(new QTableWidget(this)),
    accept_button_(new QPushButton(this)),
    office_counter_(office_count), courier_counter_(courier_count) {
  const int row_count = office_count * (office_count - 1) / 2;
  setGeometry(0, 0, 140, 110 + 600 * row_count / 21);
  table_widget_->setColumnCount(1);
  table_widget_->setRowCount(row_count);
  table_widget_->setGeometry(0, 0, 140, 700);
  QStringList qsl;
  for (int i = 1; i <= office_counter_; ++i) {
    for (int j = i + 1; j <= office_counter_; ++j) {
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
  // average distance in minutes between pairs of offices
  std::vector<std::vector<int>>
      matrix_dist(office_counter_, std::vector<int>(office_counter_));
  int cnt = 0;
  int number_of_empty_cells = 0;
  bool error_flag = false;
  for (int i = 1; i <= office_counter_ && !error_flag; ++i) {
    for (int j = i + 1; j <= office_counter_ && !error_flag; ++j) {
      auto item = table_widget_->item(cnt, 0);
      if (item) {
        if (item->text().isEmpty()) {
          number_of_empty_cells++;
        } else {
          Time dist;
          try {
            dist = Time(item->text().toStdString());
          } catch (std::logic_error &error) {
            QMessageBox::critical(this,
                                  "Ошибка заполнения времени",
                                  "Некоректный формат времени, ожидается hh:mm, время записанно в формате, как на часах, т.е. не более 23 часов и 59 минут");
            error_flag = true;
            break;
          }
          matrix_dist[i - 1][j - 1] = matrix_dist[j - 1][i - 1] = dist.getIntTime();
        }
      } else {
        ++number_of_empty_cells;
      }
      ++cnt;
    }
  }
  if (!error_flag) {
    bool next = true;
    if (number_of_empty_cells != cnt && number_of_empty_cells != 0) {
      next = false;
      cnt = 0;
      bool ask = true;
      for (int i = 1; i <= office_counter_; ++i) {
        for (int j = i + 1; j <= office_counter_; ++j) {
          auto item = table_widget_->item(cnt, 0);
          if ((item && item->text().isEmpty()) || !item) {
            if (!next && ask) {
              QDialog *dlg = new QDialog(this);
              QDialogButtonBox *btn_box = new QDialogButtonBox(dlg);
              btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

              connect(btn_box, &QDialogButtonBox::accepted, dlg, &QDialog::accept);
              connect(btn_box, &QDialogButtonBox::rejected, dlg, &QDialog::reject);

              QFormLayout *layout = new QFormLayout();
              QLabel *label = new QLabel(dlg);
              label->setText(
                  "Кажется вы недозаполнили расстояние между : " + QString::number(i) + " - " + QString::number(j)
                      + "\nи возможно ряд других\nУверены, что хотитет продолжить?");
              layout->addRow(label);
              layout->addWidget(btn_box);

              dlg->setLayout(layout);

              if (dlg->exec() == QDialog::Accepted) {
                next = true;
              }
              ask = false;
            } else {
              matrix_dist[i - 1][j - 1] = matrix_dist[j - 1][i - 1] = -1;
            }
          }
          ++cnt;
        }
      }
    }
    if (next) {
      std::cerr << "ABOBA" << std::endl;
      MainDispetcherWindow *win = new MainDispetcherWindow(office_counter_, office_counter_, matrix_dist, this);
      win->show();
    }
  }
}
