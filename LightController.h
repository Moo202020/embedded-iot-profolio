#pragma once
#include <cstdint>
class LightController {
 public:
  explicit LightController(uint32_t hold_ms=240000): hold_(hold_ms) {}
  bool update(uint32_t now, bool motion) {
    if (motion) { last_=now; on_=true; }
    else if (on_ && uint32_t(now-last_)>=hold_) on_=false;
    return on_;
  }
  bool on() const { return on_; }
 private:
  uint32_t hold_, last_=0;
  bool on_=false;
};
