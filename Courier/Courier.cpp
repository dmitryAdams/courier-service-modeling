//
// Created by Egor on 02.10.2024.
//

#include "Courier.h"

bool Courier::isOnTheWay() const { return !targets_.empty(); }

int Courier::comingFrom() const { return from_; }

int Courier::goingTo() const { return to_; }

std::string Courier::remainingTravelTime() const {
    int time = timeToNext;
    return "hh:mm";
}

void Courier::setWay(int from, int to) {
    if (targets_.empty()) timeToNext = dist_[cur_][from_].second;
    targets_.push(from);
    targets_.push(to);
}

void Courier::next(int step) {
    if (targets_.empty()) return;
    while (!targets_.empty() && step > 0) {
        if (timeToNext <= step) {
            cur_ = dist_[cur_][targets_.front()].first;
            step -= timeToNext;
            targets_.pop();
            if (!targets_.empty()) timeToNext = dist_[cur_][targets_.front()].second;
        } else timeToNext -= step;
    }
}