#include <iostream>

void f(int* p, size_t n)
{
	// P can be null?
	//if (!p) return;
	
	for (auto i=0u ; i<n ;i++) {
		std::cout << *(p+i) << ' ';
	}
	std::cout << '\n';
}

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
    // ...
	std::cout << "OK:\n";
	f(a, 10);
	std::cout << "Bad?:\n";
	f(NULL, 0); // BAD?
	std::cout << "Bad!:\n";
	f(NULL, 10); // BAD!
}
