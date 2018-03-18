#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <iostream>
#include <algorithm>
#include <gsl/gsl>

void f(gsl::span<int> arr)
{
	std::cout << "Range loop:\n";
	for (const auto x : arr) {
		std::cout << x << ' ';
	}
	std::cout << '\n';

 	std::cout << "c style loop (you need the index):\n";
	for (auto i = gsl::index{0}; i<arr.size(); i++) {
		std::cout << i << ':' << arr[i] << ' ';
	}
	std::cout << '\n';

	try {
		std::cout << "c style loop (and overflowing):\n";
		for (auto i = gsl::index{0}; i<=arr.size(); i++) {
			std::cout << i << ':' << arr[i] << ' ';
		}
		std::cout << '\n';
	} catch (const std::exception& e) {
		std::cout << "Ouch!: " << e.what() << '\n';
	}

			
	std::cout << "iterator loop:\n";
	for (auto it = std::begin(arr); it != std::end(arr); it++) {
		std::cout << *it << ' ';
	}
	std::cout << '\n';

	// Each for loop is an algorithm
	std::cout << "algorithm loop:\n";
	std::for_each(std::begin(arr), std::end(arr), [](const int x) {
		std::cout << x << ' ';
	});
	std::cout << '\n';
	
}

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	f(a);
}
