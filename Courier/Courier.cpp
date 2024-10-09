//
// Created by Egor on 02.10.2024.
//

#include "Courier.h"

#include <iostream>

bool Courier::isOnTheWay() const { return !targets_.empty(); }

int Courier::comingFrom() const { return cur_; }

int Courier::getTotalTime() const { return totalTime_; }

int Courier::getTotalFreeTime() const { return freeTime_; }

int Courier::getNextTime() const {
    return timeToNext_;
}

int Courier::goingTo() const {
    if (targets_.empty()) return cur_;
    return dist_[cur_][targets_.front()].first;
}

int Courier::getId() const { return id_; }

int Courier::getLast() const {
    if (targets_.empty()) return cur_;
    return targets_.back();
}

int Courier::timeForFree() const { return timeForFree_ + timeToNext_; }

std::string Courier::remainingTravelTime() const {
    int time = timeToNext_;
    return "hh:mm";
}

void Courier::setWay(int from, int to) {
    if (targets_.empty()) {
        timeToNext_ = dist_[cur_][dist_[cur_][from].first].second;
        timeForFree_ = dist_[cur_][from].second - timeToNext_;
    } else {
        timeForFree_ += dist_[targets_.back()][from].second;
    }
    targets_.push(from);
    timeForFree_ += dist_[from][to].second;
    targets_.push(to);
}

std::vector<Event> Courier::next(int step) {
    curTime_ += step;
    std::cout << id_ << " on " << cur_ << std::endl;
    std::vector<Event> visited;
    if (targets_.empty()) {
        std::cout << "No targets" << std::endl;
        return visited;
    }
    while (!targets_.empty() && step > 0) {
        if (timeToNext_ == dist_[cur_][dist_[cur_][targets_.front()].first].second) {
            visited.push_back({id_, 1, cur_, curTime_ - step});
        }
        if (timeToNext_ <= step) {
            std::cout << id_ << " going to next target " << targets_.front() << " throw " <<
                      dist_[cur_][targets_.front()].first << std::endl;
            cur_ = dist_[cur_][targets_.front()].first;
            if (free_) freeTime_ += timeToNext_;
            totalTime_ += timeToNext_;
            free_ = !free_;
            step -= timeToNext_;
            visited.push_back({id_, 0, cur_, curTime_ - step});
            timeForFree_ -= timeToNext_;
            timeToNext_ = 0;
            if (cur_ == targets_.front()) targets_.pop();
            if (!targets_.empty()) timeToNext_ = dist_[cur_][dist_[cur_][targets_.front()].first].second;
            timeForFree_ -= timeToNext_;
        } else {
            timeToNext_ -= step;
            if (free_) freeTime_ += step;
            totalTime_ += step;
            step = 0;
            std::cout << "Time to next branch: " << timeToNext_ << std::endl;
        }
    }
    std::cout << id_ << " on " << cur_ << std::endl;
    return visited;
}