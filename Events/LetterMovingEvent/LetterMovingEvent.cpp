//
// Created by Egor on 15.10.2024.
//

#include "LetterMovingEvent.h"

std::string LetterMovingEvent::messageOfEvent() {
    return (isTaken_ ? "Leter has been taken from office "
                     : "Letter has been delivered to office ") +
           std::to_string(officeId_) + " at time " + getStrTime(time_);
}

LetterMovingEvent::LetterMovingEvent(int isTaken, int officeId, int time)
        : isTaken_(isTaken), officeId_(officeId), time_(time) {}

bool LetterMovingEvent::isLastEvent() {
    return false;
}