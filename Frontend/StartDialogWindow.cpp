//
// Created by adams on 10/2/24.
//

#include <iostream>
#include "StartDialogWindow.h"
#include "QMessageBox"
#include "SetTimeWindow.h"
StartDialogWindow::StartDialogWindow(QWidget *parent) :
    QDialog(parent),
    office_line_edit_(new QLineEdit(this)),
    courier_line_edit_(new QLineEdit(this)),
    accept_button(new QPushButton(this)) {
  const int window_width = 700, window_height = 170, w_pending = 10, h_pending = 20;
  setGeometry(0, 0, window_width, window_height);
  const int line_edit_width = (window_width - w_pending * 3) / 2;
  const int line_edit_height = (window_height - h_pending * 3) / 2;
  {
    office_line_edit_->setPlaceholderText("Введите количество офисов:");
    office_line_edit_->setGeometry(QRect(w_pending, h_pending, line_edit_width, line_edit_height));
  }
  {
    courier_line_edit_->setPlaceholderText("Введите колиечство курьеров компании:");
    courier_line_edit_->setGeometry(QRect(line_edit_width + w_pending * 2,
                                          h_pending,
                                          line_edit_width,
                                          line_edit_height));
  }
  {
    accept_button->setText("Задать размер компании");
    accept_button->setGeometry(QRect(w_pending,
                                     line_edit_height + h_pending * 2,
                                     window_width - 2 * w_pending,
                                     line_edit_height));
    connect(accept_button, &QPushButton::clicked, this, &StartDialogWindow::accept_button_clicked);
  }
}
void StartDialogWindow::accept_button_clicked() {
  bool office_ok, courier_ok;
  int office_count = office_line_edit_->text().toInt(&office_ok),
      courier_count = courier_line_edit_->text().toInt(&courier_ok);
  if (!office_ok || office_count < 3 || office_count > 7) {
    QMessageBox::critical(this, "ошибка в вводе количества офисов", "Неправильный формат ввода числа, 3 <= x <= 7");
  } else if (!courier_ok || courier_count <= 0 || courier_count > 5) {
    QMessageBox::critical(this, "ошибка в вводе количества курьеров", "Неправильный формат ввода числа, 1 <= x <= 5");
  } else {
    hide();
    emit data_entered_correctly();
  }
}
int StartDialogWindow::office_count() {
  return office_line_edit_->text().toInt();
}
int StartDialogWindow::courier_count() {
  return courier_line_edit_->text().toInt();
}
