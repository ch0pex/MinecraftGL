#include "../public/timer.h"

Timer::Timer(std::string message, TimerMode timer_mode) {
    start_time_ = std::chrono::high_resolution_clock::now();
    mode_ = timer_mode;
    msg_ = message;
}

Timer::~Timer() {
    End();
}

void Timer::End() {
    end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_);

    switch (mode_) {
        case kSec:
            PRINT_SEC;
            break;
        case kMs:
            PRINT_MS;
            break;
        case kFps:
            PRINT_FPS;
            break;
        default:
            break;
    }
}