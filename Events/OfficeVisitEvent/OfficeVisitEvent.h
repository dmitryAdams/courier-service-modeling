//
// Created by Egor on 15.10.2024.
//

#ifndef COURIER_SERVICE_MODELING_OFFICEVISITEVENT_H
#define COURIER_SERVICE_MODELING_OFFICEVISITEVENT_H

#include "../AbstacstEvent/AbsractEvent.h"
#include <string>

class OfficeVisitEvent : public AbstractEvent {
public:
    std::string messageOfEvent() override;
    OfficeVisitEvent(bool isVisit, int officeId, int timeVisit);
    bool isLastEvent() override;

private:
    bool isVisit_;
    int officeId_;
    int timeVisit_;
};


#endif //COURIER_SERVICE_MODELING_OFFICEVISITEVENT_H
