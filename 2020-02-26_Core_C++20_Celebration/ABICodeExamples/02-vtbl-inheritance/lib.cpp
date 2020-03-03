#define LIB_VERSION 2
#include "lib.h"

#include <iostream>

bool WidgetBase::True() const
{
	std::cout << "Returns true\n";
	return true;
}

void WidgetBase::f() const
{
	std::cout << "No one calls me!\n";
}

bool Widget::False() const
{
	std::cout << "Returns false\n";
	return false;
}

void weird(const Widget& w)
{
	auto t = w.True();
	std::cout << "w.True() returned: " << t << '\n';
	auto f = w.False();
	std::cout << "w.False() returned: " << f << '\n';
}

const Widget& getWidget()
{
	static Widget w;
	return w;
}
