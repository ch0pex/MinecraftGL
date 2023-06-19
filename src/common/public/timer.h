#pragma once
#include <iostream>
#include <chrono>
#include <string>


#define PRINT_SEC std::cout << "Tiempo de ejecucion(" << msg << "): " << duration.count() / 1000.0 << "s" << std::endl
#define PRINT_FPS std::cout << "FPS(" << msg << "): " << (double) (1000.0 / duration.count())  << std::endl
#define PRINT_MS std::cout << "Tiempo de ejecucion(" << msg << "): " << duration.count() << "ms" << std::endl

enum TimerMode {
	SEC = 0,
	FPS,
	MS
};

class Timer {
private: 
	TimerMode mode; 
	std::string msg; 
	std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
public: 
	Timer(std::string message = "", TimerMode timerMode = SEC); 
	~Timer(); 
	void end(); 
};