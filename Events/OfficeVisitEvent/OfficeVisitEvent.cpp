//
// Created by Egor on 15.10.2024.
//

#include "OfficeVisitEvent.h"

std::string OfficeVisitEvent::messageOfEvent() {
    return "Office " + std::to_string(officeId_) + " has been " +
           (isVisit_ ? "visited" : "adandoned") + " at time " +
           getStrTime(timeVisit_);
}

OfficeVisitEvent::OfficeVisitEvent(bool isVisit, int officeId, int timeVisit) : isVisit_(isVisit),
                                                                                officeId_(officeId),
                                                                                timeVisit_(timeVisit) {}

bool OfficeVisitEvent::isLastEvent() {
    return false;
}