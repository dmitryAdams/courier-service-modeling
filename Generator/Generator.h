//
// Created by Egor on 04.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_GENERATOR_H
#define COURIER_SERVICE_MODELING_GENERATOR_H

#include <tuple>
#include <random>

struct Request {
    int time;
    int from;
    int to;
};

class Generator {
public:
    Generator(int branchCount);

    Request getRequest();
private:
    std::random_device rd_;
    std::mt19937 gen_;
    std::normal_distribution<long double> d_;
    std::vector<int> chose_;

    int getTime();
};

bool operator<(const Request& lhs, const Request& rhs);

#endif //COURIER_SERVICE_MODELING_GENERATOR_H
