//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_SERVICE_H
#define COURIER_SERVICE_MODELING_SERVICE_H

#include <utility>

#include "../Courier/Courier.h"
#include "../Generator/Generator.h"
#include "vector"

struct Statistics {
    int totalFreeTime;
    long double averageTimeInWork;
};

class Service {
   public:
    Service(int branchCount, int courierCount,
            std::vector<std::vector<int>> matrix, std::vector<int> sz);

    ~Service();

    void getRequest(int fromId, int toId);

    std::vector<Courier *> getCouriers();

    std::vector<Event *> nextStep(int step);

   private:
    int branchCount_, courierCount_;
    int Time_ = 540;
    Generator generator_;
    std::vector<std::vector<int>> matrix_;
    std::vector<std::vector<std::pair<int, int>>> dist_;
    std::vector<Courier *> couriers_;
    std::vector<Branch *> branches_;
    std::vector<Request> requests_;
    std::vector<int> sz_;

    void floyd();
    Statistics getStatistics();
};

#endif  // COURIER_SERVICE_MODELING_SERVICE_H
