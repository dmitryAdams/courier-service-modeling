//
// Created by Egor on 02.10.2024.
//

#include "Courier.h"

#include <iostream>

bool Courier::isOnTheWay() const { return !targets_.empty(); }

int Courier::comingFrom() const { return from_; }

int Courier::goingTo() const { return to_; }

int Courier::getId() const { return id_; }

int Courier::getLast() const { return targets_.back(); }

int Courier::timeForFree() const { return timeForFree_ - timeToNext_; }

std::string Courier::remainingTravelTime() const {
  int time = timeToNext_;
  return "hh:mm";
}

void Courier::setWay(int from, int to) {
  if (targets_.empty()) {
    timeToNext_ = dist_[cur_][from].second;
    timeForFree_ = timeToNext_;
  } else timeForFree_ += dist_[targets_.back()][from].second;
  targets_.push(from);
  timeForFree_ += dist_[targets_.back()][from].second;
  targets_.push(to);
}

void Courier::next(int step) {
  if (targets_.empty()) return;
  std::cout << id_ << " on " << cur_ << std::endl;
  while (!targets_.empty() && step > 0) {
    std::cout << "Going by step: " << step << " to " << targets_.front()
              << std::endl;
    if (timeToNext_ <= step) {
      cur_ = dist_[cur_][targets_.front()].first;
      step -= timeToNext_;
      targets_.pop();
      if (!targets_.empty()) timeToNext_ = dist_[cur_][targets_.front()].second;
    } else
      timeToNext_ -= step;
  }
  std::cout << id_ << " on " << cur_ << std::endl;
}