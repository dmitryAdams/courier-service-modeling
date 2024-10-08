//
// Created by adams on 10/7/24.
//

#include "OfficePriorityWindow.h"
#include "QMessageBox"

OfficePriorityWindow::OfficePriorityWindow(int office_counter, QWidget *parent) :
    QDialog(parent),
    line_edits_layout_(new QHBoxLayout),
    accept_button_(new QPushButton),
    main_layout_(new QVBoxLayout(this)) {

  priorities_line_edits_.resize(office_counter);
  for (int i = 0; i < office_counter; ++i) {
    priorities_line_edits_[i] = new QLineEdit(this);
    line_edits_layout_->addWidget(priorities_line_edits_[i]);
  }

  accept_button_->setText("Задать");

  main_layout_->addLayout(line_edits_layout_);
  main_layout_->addWidget(accept_button_);

  connect(accept_button_, &QPushButton::clicked, this, &OfficePriorityWindow::accept_button_clicked_);
}
void OfficePriorityWindow::accept_button_clicked_() {
  std::vector<int> priorities(priorities_line_edits_.size());
  bool full_ok = true, ok;
  for (int i = 0; i < priorities_line_edits_.size(); ++i) {
    priorities[i] = priorities_line_edits_[i]->text().toInt(&ok);
    if (ok) {
      if (priorities[i] <= 0) {
//        QMessageBox::critical(this, "Ошибка", "приоритет может быть только натуральным числом");
        full_ok = false;
        break;
      }
    }
    full_ok = full_ok && ok;
  }
  if (full_ok) {
    hide();
//    emit data_entered_correctly(priorities);
  } else {
    QMessageBox::critical(this, "Ошибка", "приоритет может быть только натуральным числом!");
  }
}
