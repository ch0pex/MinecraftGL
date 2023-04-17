#pragma once
#include <iostream>
#include <chrono>


#define PRINT_SEC std::cout << "Tiempo de ejecucion: " << duration.count() / 1000 << "s" << std::endl
#define PRINT_FPS std::cout << "FPS: " << (double) 1000 / duration.count()  << std::endl
#define PRINT_MS std::cout << "Tiempo de ejecucion: " << duration.count() << "ms" << std::endl

enum TimerMode {
	SEC = 0,
	FPS,
	MS
};

class Timer {
private: 
	TimerMode mode; 
	std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
public: 
	Timer(TimerMode _mode = SEC); 
	~Timer(); 
	void end(); 
};