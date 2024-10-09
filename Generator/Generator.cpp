//
// Created by Egor on 04.10.2024.
//

#include <random>
#include <ctime>
#include <cmath>
#include "Generator.h"

bool operator<(const Request& lhs, const Request& rhs) {
    return lhs.time < rhs.time;
}

Generator::Generator(int branchCount) : gen_(rd_()), d_(810, 75) {
    srand(time(0));
    for (int i = 1; i <= branchCount; ++i) {
        int cnt = rand() % 10;
        for (int j = 0; j < cnt; ++j) chose_.push_back(i);
    }
}

int Generator::getTime() {
    return fmax(540, fmin(1080, std::round(d_(gen_))));
}

Request Generator::getRequest() {
    Request request;
    request.time = getTime();
    request.from = chose_[rand() % chose_.size()];
    request.to = request.from;
    while (request.to == request.from) request.to = chose_[rand() % chose_.size()];
    return request;
}