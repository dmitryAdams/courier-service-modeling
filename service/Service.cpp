//
// Created by Egor on 02.10.2024.
//

#include "Service.h"
#include <algorithm>
#include <iostream>

Service::Service(int branchCount, int courierCount,
                 std::vector<std::vector<int>> matrix)
    : branchCount_(branchCount),
      courierCount_(courierCount),
      matrix_(std::move(matrix)),
      branches_(branchCount_),
      couriers_(courierCount_) ,
      generator_(branchCount_),
      dist_(branchCount_ + 1, std::vector<std::pair<int, int>>(branchCount_ + 1, {-1, 1e9})) {
  // Graph initialization
  for (int i = 1; i <= branchCount_; ++i)
    for (int j = 1; j <= branchCount_; ++j)
      if (matrix_[i][j] != 1e9)
        dist_[i][j] = {j, matrix_[i][j]};

  floyd();

  // Branches initialization
  for (int id = 1; id <= branchCount_; ++id) branches_[id - 1] = new Branch(id);

  // Couriers initialization
  for (int i = 0; i < courierCount_; ++i)
    couriers_[i] =
        new Courier(dist_, branches_[i % branchCount_]->getId(), i + 1);

  // Requests generation
  requests_.resize(1000);
  for (int i = 0; i < 1000; ++i) requests_[i] = generator_.getRequest();
  sort(requests_.rbegin(), requests_.rend());
}

Service::~Service() {
  for (Courier* courier : couriers_) delete courier;
  for (Branch* branch : branches_) delete branch;
}

void Service::nextStep(int step) {
  Time_ += step;
  while (!requests_.empty() && requests_.back().time <= Time_) {
    getRequest(requests_.back().from, requests_.back().to);
    requests_.pop_back();
  }
  for (Courier* courier : couriers_) {
    courier->next(step);
  }
}

void Service::floyd() {
  for (int i = 1; i <= branchCount_; ++i)
    for (int j = 1; j <= branchCount_; ++j)
      for (int k = 1; k <= branchCount_; ++k)
        if (dist_[j][i].second + dist_[i][k].second < dist_[j][k].second)
          dist_[j][k] = {dist_[j][i].first,
                         dist_[j][i].second + dist_[i][k].second};
}

void Service::getRequest(int fromId, int toId) {
    int id = -1;
    int dist = 1e9;
    for (Courier *courier : couriers_) {
        if (courier->timeForFree() + dist_[courier->getLast()][fromId].second < dist) {
            id = courier->getId();
            dist = courier->timeForFree() + dist_[courier->getLast()][fromId].second;
        }
    }
    couriers_[id - 1]->setWay(fromId, toId);
}

Statistics Service::getStatistics() {
  Statistics res;
  double totalTimeSum = 0;
  for (Courier *courier: couriers_) totalTimeSum += courier->getTotalTime();
  res.averageTimeInWork = totalTimeSum / courierCount_;
  int totalFreeSum = 0;
  for (Courier *courier: couriers_) totalTimeSum += courier->getTotalFreeTime();
  res.totalFreeTime = totalFreeSum;
  return res;
}