//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_SERVICE_H
#define COURIER_SERVICE_MODELING_SERVICE_H

#include <utility>

#include "../Courier/Courier.h"
#include "vector"

class Service {
public:
    Service(int branchCount, int courierCount, std::vector<std::vector<int>> matrix) :
            branchCount_(branchCount), courierCount_(courierCount), matrix_(std::move(matrix)),
            branches_(branchCount_), couriers_(courierCount_) {
        //Graph initialization
        for (int i = 1; i <= branchCount_; ++i)
            for (int j = 1; j <= branchCount_; ++j)
                if (matrix_[i][j] != 1e9) dist_[i][j] = {j, matrix_[i][j]};
                else dist_[i][j] = {-1, 1e9};

        floyd();

        //Branches initialization
        for (int id = 1; id <= branchCount_; ++id) branches_[id - 1] = new Branch(id);

        //Couriers initialization
        for (int i = 0; i < courierCount_; ++i) couriers_[i] = new Courier(dist_, branches_[i % branchCount_]->getId());
    }

    ~Service() {
        for (Courier *courier: couriers_) { delete courier; }
        for (Branch *branch: branches_) { delete branch; }
    }

    std::vector<Courier *> getCouriers();

    void nextStep(int step);

private:
    int branchCount_, courierCount_;
    std::vector<std::vector<int>> matrix_;
    std::vector<std::vector<std::pair<int, int>>> dist_;
    std::vector<Courier *> couriers_;
    std::vector<Branch *> branches_;

    void floyd();
};

#endif //COURIER_SERVICE_MODELING_SERVICE_H
