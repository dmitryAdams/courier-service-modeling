//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_COURIER_H
#define COURIER_SERVICE_MODELING_COURIER_H

#include "../Branch//Branch.h"
#include <string>
#include <vector>
#include <queue>

class Courier {
public:
    Courier(const std::vector<std::vector<std::pair<int, int>>>& dist, int cur) : dist_(dist), cur_(cur) {}

    bool isOnTheWay() const;

    void setWay(int from, int to);

    int comingFrom() const;

    int goingTo() const;

    std::string remainingTravelTime() const;

    void next(int step);

private:
    int from_ = -1;
    int to_ = -1;
    int cur_ = -1;
    int timeToNext = 1e9;

    const std::vector<std::vector<std::pair<int, int>>>& dist_;
    std::queue<int> targets_;
};


#endif //COURIER_SERVICE_MODELING_COURIER_H
