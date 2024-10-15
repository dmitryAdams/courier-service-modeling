//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_COURIER_H
#define COURIER_SERVICE_MODELING_COURIER_H

#include <queue>
#include <string>
#include <vector>

#include "../Branch//Branch.h"
#include "../Events/AbstacstEvent/AbsractEvent.h"

class Courier {
public:
    Courier(const std::vector<std::vector<std::pair<int, int>>> &dist, std::vector<Branch *> branches, int cur, int id)
            : dist_(dist), cur_(cur), id_(id), timeForFree_(0), timeToNext_(0), branches_(std::move(branches)) {}

    int getId() const;

    bool isOnTheWay() const;

    void setWay(int from, int to);

    int comingFrom() const;

    int goingTo() const;

    int timeForFree() const;

    int getLast() const;

    int getTotalTime() const;

    int getTotalFreeTime() const;

    int getNextTime() const;

    void clearTargets();

    std::string remainingTravelTime() const;

    std::vector<AbstractEvent *> next(int step);

    std::vector<AbstractEvent *> next3(int step);

private:
    int id_;
    int cur_ = -1;
    int timeToNext_;
    int timeForFree_;
    const std::vector<std::vector<std::pair<int, int>>> &dist_;
    const std::vector<Branch *> branches_;
    std::queue<int> targets_;
    std::vector<int> ends_;
    int weight_ = 0;
    int freeTime_ = 0;
    int totalTime_ = 0;
    int curTime_ = 540;
};

#endif  // COURIER_SERVICE_MODELING_COURIER_H
