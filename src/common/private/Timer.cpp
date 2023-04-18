#include "../public/Timer.h"

Timer::Timer(std::string message, TimerMode timerMode)
{
    start_time = std::chrono::high_resolution_clock::now();
	mode = timerMode;
    msg = message ; 
}

Timer::~Timer() 
{
	end();  
}

void Timer::end()
{
    end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    switch(mode)
    {
    case SEC: PRINT_SEC; break; 
    case MS: PRINT_MS; break; 
    case FPS: PRINT_FPS; break; 
    default: break; 
    }
}