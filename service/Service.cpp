//
// Created by Egor on 02.10.2024.
//

#include "Service.h"

void Service::nextStep(int step) {
    for (Courier *courier: couriers_) {
        courier->next(step);
    }
}

void Service::floyd() {
    for (int i = 1; i <= branchCount_; ++i)
        for (int j = 1; j <= branchCount_; ++j)
            for (int k = 1; k <= branchCount_; ++k)
                if (dist_[j][i].second + dist_[i][k].second < dist_[j][k].second)
                    dist_[j][k] = {dist_[j][i].first, dist_[j][i].second + dist_[i][k].second};
}