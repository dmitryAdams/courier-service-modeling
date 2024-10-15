//
// Created by Egor on 15.10.2024.
//

#include "OfficeVisitEvent.h"

std::string getStrTimeForBack2(int t) {
    std::string ti;
    if (t < 600) ti.push_back('0');
    ti += std::to_string(t / 60);
    ti.push_back(':');
    if (t % 60 < 10) ti.push_back('0');
    ti += std::to_string(t % 60);
    return ti;
}

std::string OfficeVisitEvent::messageOfEvent() {
    return "Office " + std::to_string(officeId_) + " has been " +
           (isVisit_ ? "visited" : "adandoned") + " at time " +
           getStrTimeForBack2(timeVisit_);
}

OfficeVisitEvent::OfficeVisitEvent(bool isVisit, int officeId, int timeVisit)
    : isVisit_(isVisit), officeId_(officeId), timeVisit_(timeVisit) {}

bool OfficeVisitEvent::isLastEvent() { return false; }