//
// Created by Egor on 15.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_LETTERMOVINGEVENT_H
#define COURIER_SERVICE_MODELING_LETTERMOVINGEVENT_H

#include "../AbstacstEvent/AbsractEvent.h"

class LetterMovingEvent : public AbstractEvent {
   public:
    std::string messageOfEvent() override;
    LetterMovingEvent(int isTaken, int officeId, int time);
    bool isLastEvent() override;

   private:
    bool isTaken_;
    int officeId_;
    int time_;
};

#endif  // COURIER_SERVICE_MODELING_LETTERMOVINGEVENT_H
