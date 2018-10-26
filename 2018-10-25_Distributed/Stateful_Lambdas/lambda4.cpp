#include <vector>      // vector, duh
#include <iterator>    // ostream_iterator
#include <iostream>    // cout
#include <algorithm>   // copy & generate_n

void SomeInterestingTest()
{
	std::vector<char> v;
	std::generate_n(std::back_inserter(v), 26,
				  [c = 'a']() mutable {
					  return c++;
				  }
		);
	// Do something with v
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<char>(std::cout, ","));
}

int main()
{
	SomeInterestingTest();
}

