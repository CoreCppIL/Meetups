#include <boost/asio.hpp>
#include <iostream>
#include "../common/timestamp.h"

namespace asio = boost::asio;
namespace posix_time = boost::posix_time;
namespace chrono = std::chrono;

int main()
{
	asio::io_service service;

	asio::deadline_timer timer(service, boost::posix_time::seconds(3));

	timer.async_wait([](auto err) {
		std::cout << timestamp << ": Timer expired!\n";
	});

	std::cout << timestamp << ": Calling run\n";
	service.run();
	std::cout << timestamp << ": Done\n";
}
