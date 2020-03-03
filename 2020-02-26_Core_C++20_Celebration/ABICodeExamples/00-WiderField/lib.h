#pragma once

#include <iosfwd>

class Widget
{
#if LIB_VERSION == 1
	using T = char;
#elif LIB_VERSION == 2
	using T = int;
#endif

public:
	Widget(T val) : val_(val) {}
	friend std::ostream& operator<< (std::ostream& ostr, const Widget& widget);

private:
	T val_;
};
