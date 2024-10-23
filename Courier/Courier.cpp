//
// Created by Egor on 02.10.2024.
//

#include "Courier.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "../Events/LetterMovingEvent/LetterMovingEvent.h"
#include "../Events/OfficeVisitEvent/OfficeVisitEvent.h"

bool Courier::isOnTheWay() const { return !targets_.empty(); }

int Courier::comingFrom() const { return cur_; }

int Courier::getTotalTime() const { return totalTime_; }

int Courier::getTotalFreeTime() const { return freeTime_; }

int Courier::getNextTime() const { return timeToNext_; }

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
        timeForFree_ += dist_[from][to].second;
    }
    branches_[from - 1]->addId(to);
    targets_.push(from);
    targets_.push(to);
}

std::vector<AbstractEvent *> Courier::next(int step) {
    if (targets_.empty()) return {};
    std::vector<AbstractEvent *> res;
    while (!targets_.empty() && step > 0) {
        if (timeToNext_ ==
            dist_[cur_][dist_[cur_][targets_.front()].first].second) {
            res.push_back(new OfficeVisitEvent(0, cur_, curTime_));
            for (int branchId : branches_[cur_ - 1]->getIdVec()) {
                res.push_back(new LetterMovingEvent(1, cur_, curTime_));
                ends_.push_back(branchId);
                targets_.push(branchId);
                ++weight_;
            }
        }
        if (timeToNext_ <= step) {
            curTime_ += timeToNext_;
            if (weight_ == 0) freeTime_ += timeToNext_;
            cur_ = dist_[cur_][targets_.front()].first;
            res.push_back(new OfficeVisitEvent(1, cur_, curTime_));
            for (int i = 0; i < std::count(ends_.begin(), ends_.end(), cur_);
                 ++i) {
                res.push_back(new LetterMovingEvent(0, cur_, curTime_));
                --weight_;
            }
            ends_.erase(ends_.begin(),
                        std::remove(ends_.begin(), ends_.end(), cur_));
            totalTime_ += timeToNext_;
            step -= timeToNext_;
            timeForFree_ -= timeToNext_;
            timeToNext_ = 0;
            if (cur_ == targets_.front()) {
                targets_.pop();
            }
            if (!targets_.empty()) {
                timeToNext_ =
                    dist_[cur_][dist_[cur_][targets_.front()].first].second;
                timeForFree_ -= timeToNext_;
            }
        } else {
            timeToNext_ -= step;
            if (weight_ == 0) freeTime_ += step;
            totalTime_ += step;
            curTime_ += step;
            step = 0;
        }
    }
    return res;
}

void Courier::clearTargets() {
    while (!targets_.empty()) targets_.pop();
}