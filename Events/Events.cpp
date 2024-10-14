#include "Events.h"

std::string getStrTime(int t) {
    std::string ti;
    if (t < 600) ti.push_back('0');
    ti += std::to_string(t / 60);
    ti.push_back(':');
    if (t % 60 < 10) ti.push_back('0');
    ti += std::to_string(t % 60);
    return ti;
}

std::string LatsEvent::getString() { return "Work has been ended"; }

std::string OfficeVisitEvent::getString() {
    return "Office " + std::to_string(officeId_) + " has been " +
           (isVisit_ ? "visited" : "adandoned") + " at time " +
           getStrTime(timeVisit_);
}

OfficeVisitEvent::OfficeVisitEvent(bool isVisit, int officeId, int timeVisit)
    : isVisit_(isVisit), officeId_(officeId), timeVisit_(timeVisit) {}

std::string LetterMovingEvent::getString() {
    return (isTaken_ ? "Leter has been taken from office "
                     : "Letter has been delivered to office ") +
           std::to_string(officeId_) + " at time " + getStrTime(time_);
}

LetterMovingEvent::LetterMovingEvent(int isTaken, int officeId, int time)
    : isTaken_(isTaken), officeId_(officeId), time_(time) {}