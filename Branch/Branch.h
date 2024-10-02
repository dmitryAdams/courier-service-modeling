//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_BRANCH_H
#define COURIER_SERVICE_MODELING_BRANCH_H

class Branch {
public:
    Branch(int id) : id_(id) {}
    int getId() { return id_; }

private:
    int id_;
};


#endif //COURIER_SERVICE_MODELING_BRANCH_H
