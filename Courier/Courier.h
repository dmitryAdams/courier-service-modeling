//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_COURIER_H
#define COURIER_SERVICE_MODELING_COURIER_H

#include <queue>
#include <string>
#include <vector>

#include "../Branch//Branch.h"

class Courier {
 public:
  Courier(const std::vector<std::vector<std::pair<int, int>>>& dist, int cur, int id)
      : dist_(dist), cur_(cur), id_(id), timeForFree_(0) {}

  int getId() const;

  bool isOnTheWay() const;

  void setWay(int from, int to);

  int comingFrom() const;

  int goingTo() const;

  int timeForFree() const;

  int getLast() const;

  std::string remainingTravelTime() const;

  void next(int step);

 private:
  int id_;
  int from_ = -1;
  int to_ = -1;
  int cur_ = -1;
  int timeToNext_ = 1e9;
  int timeForFree_;
  const std::vector<std::vector<std::pair<int, int>>>& dist_;
  std::queue<int> targets_;
};

#endif  // COURIER_SERVICE_MODELING_COURIER_H
