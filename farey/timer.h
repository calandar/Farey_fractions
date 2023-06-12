#pragma once
#include <string>
#include <iostream>
#include <chrono>
class timer
{
public:
	timer(std::ostream& os, const std::string& mess);
	~timer();
private:
	std::chrono::steady_clock::time_point begin;
	std::ostream& out;
	std::string message;
};

