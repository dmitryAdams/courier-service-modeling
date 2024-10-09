//
// Created by adams on 10/2/24.
//

#include "Time.h"

std::ostream &operator<<(std::ostream &out, const Time &t) {
  out << t.getStringTime();
  return out;
}

Time operator+(Time a, const Time &b) {
  a.t_ += b.t_;
  return a;
}

std::string Time::getStringTime() const {
  return (t_ / 60 < 10 ? "0" : "") + std::to_string(t_ / 60) + ":" + (t_ % 60 < 10 ? "0" : "") + std::to_string(t_ % 60);
}

Time::Time(int minutes) : t_(minutes) {}

Time::Time(const std::string &string_time) {
  if (string_time.empty()) {
    t_ = 0;
  } else if (string_time.size() != 5 || string_time[2] != ':') {
    throw std::logic_error("Wrong Len of Time Format");
  } else {
    t_ = 60 * std::stoi(string_time.substr(0, 2));
    if (t_ > 23 * 60) throw std::logic_error("Wrong Time on Wathes");
    int tmp = std::stoi(string_time.substr(3, 2));
    if (tmp > 59) throw std::logic_error("Wrong Time on Wathes");
    t_ += tmp;
  }
}

Time::Time(const Time &t) : t_(t.t_) {}

Time &Time::operator=(const Time &t) {
  t_ = t.t_;
  return *this;
}
int Time::getIntTime() const {
  return t_;
}
