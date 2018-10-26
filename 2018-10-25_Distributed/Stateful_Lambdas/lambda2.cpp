#include <vector>      // vector, duh
#include <iterator>    // ostream_iterator
#include <iostream>    // cout
#include <algorithm>   // copy
#include <numeric>     // iota

void SomeInterestingTest()
{
	std::vector<char> v(26);
	std::iota(std::begin(v), std::end(v), 'a');

	// Do something with v
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<char>(std::cout, ","));
}

int main()
{
	SomeInterestingTest();
}

