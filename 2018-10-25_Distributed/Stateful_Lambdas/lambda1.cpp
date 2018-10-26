#include <vector>      // vector, duh
#include <iterator>    // ostream_iterator
#include <iostream>    // cout
#include <algorithm>   // copy

void SomeInterestingTest()
{
	std::vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	// Do something with v
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<char>(std::cout, ","));
}

int main()
{
	SomeInterestingTest();
}

