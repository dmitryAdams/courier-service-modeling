//
// Created by adams on 10/9/24.
//

#ifndef COURIER_SERVICE_MODELING_EVENTS_LASTEVENT_LASTEVENT_H_
#define COURIER_SERVICE_MODELING_EVENTS_LASTEVENT_LASTEVENT_H_

#include "../AbstacstEvent/AbsractEvent.h"

class LastEvent : public AbstractEvent {
 public:
  LastEvent() = default;
  std::string messageOfEvent() override;
  bool isLastEvent() override;
};

#endif //COURIER_SERVICE_MODELING_EVENTS_LASTEVENT_LASTEVENT_H_
