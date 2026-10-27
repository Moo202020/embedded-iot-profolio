#pragma once
#include <cstdint>
#include <cstddef>
inline uint32_t adcMillivolts(uint32_t raw,uint32_t maxCount=4095,uint32_t referenceMv=3300) {
  if (maxCount==0) return 0;
  if (raw>maxCount) raw=maxCount;
  return static_cast<uint32_t>((uint64_t(raw)*referenceMv)/maxCount);
}
// Feed UART bytes from task/main context. Overflowed lines are discarded.
template<std::size_t N> class LineParser {
  static_assert(N>1,"Line buffer must fit data and terminator");
 public:
  bool feed(char c) {
    if (c=='\r') return false;
    if (c=='\n') {
      bool ready=!overflow_ && used_>0;
      data_[used_]='\0'; used_=0; overflow_=false;
      return ready;
    }
    if (overflow_) return false;
    if (used_>=N-1) { overflow_=true; return false; }
    data_[used_++]=c; return false;
  }
  const char* line() const { return data_; } // Consume before feeding next byte.
 private:
  char data_[N]{};
  std::size_t used_=0;
  bool overflow_=false;
};
