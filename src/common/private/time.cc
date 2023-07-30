#include "common/public/time.h"

using namespace std::chrono;

microseconds Time::Now() {
  return time_point_cast<microseconds>(high_resolution_clock::now()).time_since_epoch();
}