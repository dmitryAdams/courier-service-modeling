//
// Created by Egor on 02.10.2024.
//

#include "Service.h"

#include <algorithm>
#include <iostream>

#include "../Events/LastEvent/LastEvent.h"

Service::Service(int branchCount, int courierCount,
                 std::vector<std::vector<int>> matrix, std::vector<int> sz)
    : branchCount_(branchCount),
      courierCount_(courierCount),
      matrix_(std::move(matrix)),
      branches_(branchCount_),
      couriers_(courierCount_),
      generator_(branchCount_, std::move(sz)),
      dist_(branchCount_ + 1,
            std::vector<std::pair<int, int>>(branchCount_ + 1, {-1, 1e9})),
      way_(3) {
    // Graph initialization
    for (int i = 1; i <= branchCount_; ++i)
        for (int j = 1; j <= branchCount_; ++j)
            if (matrix_[i][j] != 1e9) dist_[i][j] = {j, matrix_[i][j]};

    floyd();

    // Branches initialization
    for (int id = 1; id <= branchCount_; ++id)
        branches_[id - 1] = new Branch(id);

    // Couriers initialization
    for (int i = 0; i < courierCount_; ++i)
        couriers_[i] = new Courier(dist_, branches_,
                                   branches_[i % branchCount_]->getId(), i + 1);

    // Requests generation
    requests_.resize(50);
    for (int i = 0; i < 50; ++i) requests_[i] = generator_.getRequest();
    sort(requests_.rbegin(), requests_.rend());
}

Service::~Service() {
    for (Courier *courier : couriers_) delete courier;
    for (Branch *branch : branches_) delete branch;
}

std::vector<AbstractEvent *> Service::nextStep(int step) {
    if (requests_.empty()) {
        for (Courier *courier : couriers_) courier->clearTargets();
        return {new LastEvent()};
    }
    Time_ += step;
    std::vector<AbstractEvent *> res;
    while (!requests_.empty() && requests_.back().time <= Time_) {
        if (requests_.back().time + step <= 1080)
            getRequest(requests_.back().from, requests_.back().to);
        requests_.pop_back();
    }
    for (Courier *courier : couriers_) {
        std::vector<AbstractEvent *> courierEvents = courier->next(step);
        res.insert(res.end(), courierEvents.begin(), courierEvents.end());
    }
    return res;
}

void Service::floyd() {
    for (int i = 1; i <= branchCount_; ++i)
        for (int j = 1; j <= branchCount_; ++j)
            for (int k = 1; k <= branchCount_; ++k)
                if (dist_[j][i].second + dist_[i][k].second <
                    dist_[j][k].second)
                    dist_[j][k] = {dist_[j][i].first,
                                   dist_[j][i].second + dist_[i][k].second};
}

void Service::getRequest(int fromId, int toId) {
    int id;
    switch (way_) {
        case 1:
            id = getCourierId1(fromId);
            break;
        case 2:
            id = getCourierId2();
            break;
        case 3:
            id = getCourierId3(fromId, toId);
    }
    if (id != -1) {
        couriers_[id - 1]->setWay(fromId, toId);
    }
}

Stat Service::getStat() {
    Stat res;
    double totalTimeSum = 0;
    res.totalFreeTime = 0;
    for (Courier *courier : couriers_) {
        totalTimeSum += courier->getTotalTime();
        res.totalFreeTime += courier->getTotalFreeTime();
    }
    res.averageTime = totalTimeSum / courierCount_;
    return res;
}

std::vector<Courier *> Service::getCouriers() { return couriers_; }

int Service::getCourierId1(int fromId) {
    int id = -1;
    int dist = 1e9;
    for (Courier *courier : couriers_) {
        if (courier->timeForFree() + dist_[courier->getLast()][fromId].second <
            dist) {
            id = courier->getId();
            dist = courier->timeForFree() +
                   dist_[courier->getLast()][fromId].second;
        }
    }
    return id;
}

int Service::getCourierId2() { return 1 + rand() % courierCount_; }

int Service::getCourierId3(int fromId, int toId) {
    int d = 1e9;
    int id = -1;
    for (Courier *courier : couriers_) {
        if (courier->timeForFree() == 0 &&
            dist_[courier->getLast()][fromId].second < d) {
            d = dist_[courier->getLast()][fromId].second;
            id = courier->getId();
        }
    }
    if (id == -1) {
        branches_[fromId - 1]->addId(toId);
    }
    return id;
}