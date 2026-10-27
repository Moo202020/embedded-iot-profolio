#pragma once
#include <cstdint>
class DistanceAlarm {
 public:
  bool update(uint16_t mm, bool valid) {
    if (!valid) { alarm_=false; return false; }
    if (mm<=150) alarm_=true;
    else if (mm>=180) alarm_=false;
    return alarm_;
  }
 private: bool alarm_=false;
};
