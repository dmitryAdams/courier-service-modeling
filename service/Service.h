//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_SERVICE_H
#define COURIER_SERVICE_MODELING_SERVICE_H

#include "../Courier/Courier.h"
#include "vector"

class Service {
 public:
  Service(int branch_counter, int courier_counter, std::vector<int> couriers_start_position) :
      branch_counter_(branch_counter),
      courier_counter_(courier_counter) {}
  std::vector<Courier *> getCouriers() {
    std::vector<Courier *> to_send(courier_counter_);
    for (auto &i : to_send) i = new Courier();
    return to_send;
  }
  void nextStep();

 private:
  int branch_counter_, courier_counter_;
};

#endif //COURIER_SERVICE_MODELING_SERVICE_H
