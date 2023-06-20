#pragma once

#include <iostream>
#include <chrono>
#include <string>


#define PRINT_SEC std::cout << "Tiempo de ejecucion(" << msg_ << "): " << duration.count() / 1000.0 << "s" << std::endl
#define PRINT_FPS std::cout << "kFps(" << msg_ << "): " << (double) (1000.0 / duration.count())  << std::endl
#define PRINT_MS std::cout << "Tiempo de ejecucion(" << msg_ << "): " << duration.count() << "ms" << std::endl

enum TimerMode {
    kSec = 0,
    kFps,
    kMs
};

class Timer {
private:
    TimerMode mode_;
    std::string msg_;
    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point end_time;
public:
    Timer(std::string message = "", TimerMode timer_mode = kSec);
    ~Timer();
    void End();
};