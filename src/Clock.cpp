#include "../inc/Clock.h"

void Clock::start()
{
	time1 = std::chrono::high_resolution_clock::now();
}

void Clock::stop()
{
	time2 = std::chrono::high_resolution_clock::now();
	time = (std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)).count();
}

void Clock::printResult()
{
	std::cout << std::endl;
	std::cout << "Wykonanie algorytmu zajelo: " << (std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)).count() << " us.";
	std::cout << std::endl;
}


