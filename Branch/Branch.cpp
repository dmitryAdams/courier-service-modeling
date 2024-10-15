//
// Created by Egor on 02.10.2024.
//

#include "Branch.h"

Branch::Branch(int id) : id_(id) {}

void Branch::addId(int id) { requestsId_.push_back(id); }

int Branch::getId() { return id_; }

std::vector<int> Branch::getIdVec() { return requestsId_; }