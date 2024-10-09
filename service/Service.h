//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_SERVICE_H
#define COURIER_SERVICE_MODELING_SERVICE_H

#include <utility>

#include "../Courier/Courier.h"
#include "../Generator/Generator.h"
#include "vector"

class Service {
public:
    Service(int branchCount, int courierCount, std::vector<std::vector<int>> matrix);

    ~Service();

    void getRequest(int fromId, int toId);

    std::vector<Courier *> getCouriers();

    void nextStep(int step);

private:
    int branchCount_, courierCount_;
    int Time_ = 540;
    Generator generator_;
    std::vector<std::vector<int>> matrix_;
    std::vector<std::vector<std::pair<int, int>>> dist_;
    std::vector<Courier *> couriers_;
    std::vector<Branch *> branches_;
    std::vector<Request> requests_;

    void floyd();
    void getStatistics();
};

#endif //COURIER_SERVICE_MODELING_SERVICE_H
