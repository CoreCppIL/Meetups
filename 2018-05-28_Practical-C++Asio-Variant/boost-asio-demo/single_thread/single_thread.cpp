#include <boost/asio.hpp>
#include <iostream>
#include "../common/timestamp.h"

namespace asio = boost::asio;
namespace posix_time = boost::posix_time;
namespace chrono = std::chrono;

int main()
{
	asio::io_service service;

	asio::deadline_timer timer1(service, boost::posix_time::seconds(3));
	asio::deadline_timer timer2(service, boost::posix_time::seconds(3));

	timer1.async_wait([](auto err) {
		std::cout << timestamp << ": Timer 1 expired!\n";
	});

	timer2.async_wait([](auto err) {
		std::cout << timestamp << ": Timer 2 expired!\n";
	});

	std::thread main_loop([&]() { 
		std::cout << timestamp << ": Starting io_service\n";
		service.run();
	});
	main_loop.join();
}
