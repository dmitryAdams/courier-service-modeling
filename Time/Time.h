//
// Created by adams on 10/2/24.
//

#ifndef COURIER_SERVICE_MODELING_TIME_TIME_H_
#define COURIER_SERVICE_MODELING_TIME_TIME_H_

#include <algorithm>
#include "string"
#include "stdexcept"
#include "QTime"

class Time {
 public:
  Time(const std::string &string_time);
  explicit Time(int minutes = 0);
  Time(const Time &t);
  Time &operator=(const Time &t);
  std::string getStringTime() const;
  int getIntTime() const;
  friend Time operator+(Time a, const Time &b);
  friend std::ostream &operator<<(std::ostream &out, const Time &t);
 private:
  int t_;
};

#endif //COURIER_SERVICE_MODELING_TIME_TIME_H_
