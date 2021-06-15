#pragma once
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

class Clock {

private:
	std::chrono::high_resolution_clock::time_point time1; //czas początkowy
	std::chrono::high_resolution_clock::time_point time2; //czas końcowy
public:
	long time;
	void start(); //uruchom zegar
	void stop(); //zatrzymaj zegar
	void printResult(); //wyswietl zmierzony czas
};

