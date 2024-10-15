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

std::string getStrTime(int t) {
    std::string ti;
    if (t < 600) ti.push_back('0');
    ti += std::to_string(t / 60);
    ti.push_back(':');
    if (t % 60 < 10) ti.push_back('0');
    ti += std::to_string(t % 60);
    return ti;
}

#endif //COURIER_SERVICE_MODELING_EVENTS_ABSTACSTEVENT_ABSRACTEVENT_H_
