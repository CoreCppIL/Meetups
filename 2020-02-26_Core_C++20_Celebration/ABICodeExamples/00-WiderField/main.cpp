#define LIB_VERSION 1
#include "lib.h"

#include <iostream>

int main()
{
	auto w = Widget('a');
	std::cout << w << '\n';
}
