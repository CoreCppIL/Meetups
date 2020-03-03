#define LIB_VERSION 1
#include "lib.h"

#include <iostream>

void test(const Widget& w)
{
	auto t = w.True();
	std::cout << "w.True() returned: " << t << '\n';
	auto f = w.False();
	std::cout << "w.False() returned: " << f << '\n';
}

int main()
{
	auto w = Widget();
	test(w);
	test(getWidget());

	weird(w); // crash!
}
