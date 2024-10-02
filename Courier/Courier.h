//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_COURIER_H
#define COURIER_SERVICE_MODELING_COURIER_H

#include "../Branch//Branch.h"

class Courier {
public:
    bool isOnTheWay() { return onWay_; }
    void setWay(Branch* from, Branch* to) {
        from_ = from;
        to_ = to;
        onWay_ = true;
    }
private:
    bool onWay_ = false;
    Branch* from_ = nullptr;
    Branch* to_ = nullptr;
};


#endif //COURIER_SERVICE_MODELING_COURIER_H
