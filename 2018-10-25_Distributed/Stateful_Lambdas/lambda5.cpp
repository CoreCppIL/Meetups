#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <utility>
#include <chrono>
#include <iomanip>

struct Employee
{
	int id;
	std::string name;
	std::chrono::system_clock::time_point joining_date;
	int dept;
};

std::ostream& operator <<(std::ostream &o, const Employee& e)
{
	auto time_t_joining = std::chrono::system_clock::to_time_t(e.joining_date);
	o << "Emp{" << e.id << ", " 
	  << e.name << ", " 
	  << std::put_time(std::localtime(&time_t_joining), "%Y-%m-%d") << ", " 
	  << e.dept << "}" ;
	return o;
  }

void SomeInterestingTest()
{
	std::vector<Employee> v;
 	std::generate_n(std::back_inserter(v), 20,
					[i = 1000,
					 joining = std::chrono::system_clock::now() - std::chrono::hours(600*24)
					]() mutable {
						++i;
						joining -= std::chrono::hours(i/10*24);
						return Employee{ i, "Name_"+ std::to_string(i),  joining, i % 12 };
				  }
		);
	// Do something with v
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<Employee>(std::cout, ",\n"));
}

int main()
{
	SomeInterestingTest();
}

