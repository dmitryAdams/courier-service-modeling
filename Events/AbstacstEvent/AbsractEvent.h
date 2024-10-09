//
// Created by adams on 10/9/24.
//

#ifndef COURIER_SERVICE_MODELING_EVENTS_ABSTACSTEVENT_ABSRACTEVENT_H_
#define COURIER_SERVICE_MODELING_EVENTS_ABSTACSTEVENT_ABSRACTEVENT_H_

#include "string"

class AbstractEvent {
 public:
  virtual std::string messageOfEvent() = 0;
  virtual bool isLastEvent() = 0;
};

#endif //COURIER_SERVICE_MODELING_EVENTS_ABSTACSTEVENT_ABSRACTEVENT_H_
