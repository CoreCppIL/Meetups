#include <vector>      // vector, duh
#include <iterator>    // ostream_iterator
#include <iostream>    // cout
#include <algorithm>   // copy & generate

void SomeInterestingTest()
{
	std::vector<char> v(26);
	std::generate(std::begin(v), std::end(v),
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

