#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <iostream>
#include <gsl/gsl>

void f(gsl::span<int> arr)
{
	for (const auto x : arr) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
    // ...
	std::cout << "OK:\n";
	f(a);

	std::cout << "verbose:\n";
	f(gsl::span<int>{a});
	
	std::cout << "With diamentions:\n";
	f(gsl::span<int, 10>{a, 10});
	
	std::cout << "rvalue:\n";
	f({a, 10});
	
   	std::cout << "Rvalues are not really protected:\n";
	f({a, 20});

	try {
		std::cout << "Can't oversize:\n";
		f(gsl::span<int, 10>{a, 20});
	} catch (const std::exception& e) {
		std::cout << "Ouch!: " << e.what() << '\n';
	}
	try {
		std::cout << "And not undersize as well:\n";
		f(gsl::span<int, 10>{a, 5});
	} catch (const std::exception& e) {
		std::cout << "Ouch!: " << e.what() << '\n';
	}

	std::cout << "But this works:\n";
	f(gsl::span<int>{a, 5});

	std::cout << "And this works as well:\n";
	f(gsl::span<int>{a, 20});

}
