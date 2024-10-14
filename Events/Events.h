//
// Created by Egor 14.10.24
//

#ifndef COURIER_SERVICE_MODELING_EVENTS_H
#define COURIER_SERVICE_MODELING_EVENTS_H

#include <string>

class Event {
   public:
    virtual std::string getString() = 0;
};

class OfficeVisitEvent : Event {
   public:
    std::string getString() override;
    OfficeVisitEvent(bool isVisit, int officeId, int timeVisit);

   private:
    bool isVisit_;
    int officeId_;
    int timeVisit_;
};

class LetterMovingEvent : Event {
   public:
    std::string getString() override;
    LetterMovingEvent(int isTaken, int officeId, int time);

   private:
    bool isTaken_;
    int officeId_;
    int time_;
};

class LatsEvent : Event {
   public:
    std::string getString() override;
};

#endif