//
// Created by Egor on 15.10.2024.
//

#include "LetterMovingEvent.h"

std::string getStrTimeForBack(int t) {
    std::string ti;
    if (t < 600) ti.push_back('0');
    ti += std::to_string(t / 60);
    ti.push_back(':');
    if (t % 60 < 10) ti.push_back('0');
    ti += std::to_string(t % 60);
    return ti;
}

std::string LetterMovingEvent::messageOfEvent() {
    return (isTaken_ ? "Leter has been taken from office "
                     : "Letter has been delivered to office ") +
           std::to_string(officeId_) + " at time " + getStrTimeForBack(time_);
}

LetterMovingEvent::LetterMovingEvent(int isTaken, int officeId, int time)
    : isTaken_(isTaken), officeId_(officeId), time_(time) {}

bool LetterMovingEvent::isLastEvent() { return false; }