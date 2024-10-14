//
// Created by Egor on 04.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_GENERATOR_H
#define COURIER_SERVICE_MODELING_GENERATOR_H

#include <random>
#include <tuple>

struct Request {
    int time;
    int from;
    int to;
};

class Generator {
   public:
    Generator(int branchCount, std::vector<int> sz);

    Request getRequest();

   private:
    std::random_device rd_;
    std::mt19937 gen_;
    std::normal_distribution<long double> d_;
    std::vector<int> chose_;

    int getTime();
};

bool operator<(const Request& lhs, const Request& rhs);

#endif  // COURIER_SERVICE_MODELING_GENERATOR_H
