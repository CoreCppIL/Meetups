#define LIB_VERSION 2
#include "lib.h"

#include <iostream>
#include <iomanip>

std::ostream& operator<< (std::ostream& ostr, const Widget& widget)
{
	return ostr << std::hex << widget.val_;
}
