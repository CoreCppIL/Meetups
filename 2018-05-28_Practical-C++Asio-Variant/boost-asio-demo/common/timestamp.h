#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

class Timestamp {};
Timestamp timestamp;
std::ostream& operator<<(std::ostream& os, Timestamp ts)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	os << std::put_time(std::localtime(&now_c), "%F %T");

	return os;
}

