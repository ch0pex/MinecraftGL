#pragma once

#include <iostream>
#include <chrono>
#include <string>


class Time {
private:
  static float last_frame_time_;
public:
  inline static float GetLastFrameTime() { return last_frame_time_; }
  inline static void SetLastFrameTime(float last_frame_time) { last_frame_time_ = last_frame_time; }
  static std::chrono::microseconds Now();
};