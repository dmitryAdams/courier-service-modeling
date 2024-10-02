//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_SERVICE_H
#define COURIER_SERVICE_MODELING_SERVICE_H

#include "../Courier/Courier.h"
#include "vector"

class Service {
 public:
  Service(int branch_counter, int courier_counter, std::vector<int> couriers_start_position);
  std::vector<Courier *> getCouriers();
  void nextStep();

 private:

};

#endif //COURIER_SERVICE_MODELING_SERVICE_H
