//
// Created by Egor on 02.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_BRANCH_H
#define COURIER_SERVICE_MODELING_BRANCH_H

#include <vector>

class Branch {
public:
    Branch(int id);
    int getId();
    void addId(int id);
    std::vector<int> getIdVec();

private:
    int id_;
    std::vector<int> requestsId_;
};


#endif //COURIER_SERVICE_MODELING_BRANCH_H
