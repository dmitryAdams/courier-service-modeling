//
// Created by Egor on 04.10.2024.
//

#include "Generator.h"

#include <cmath>
#include <ctime>
#include <random>

bool operator<(const Request& lhs, const Request& rhs) {
    return lhs.time < rhs.time;
}

Generator::Generator(int branchCount, std::vector<int> sz)
    : gen_(rd_()), d_(810, 90) {
    srand(time(0));
    for (int i = 1; i <= branchCount; ++i) {
        for (int j = 0; j < sz[i]; ++j) chose_.push_back(i);
    }
}

int Generator::getTime() { return std::round(d_(gen_)); }

Request Generator::getRequest() {
    Request request;
    request.time = getTime();
    request.from = chose_[rand() % chose_.size()];
    request.to = request.from;
    while (request.to == request.from)
        request.to = chose_[rand() % chose_.size()];
    return request;
}