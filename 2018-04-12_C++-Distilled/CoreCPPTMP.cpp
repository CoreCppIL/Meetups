#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>

template <typename...>
struct typelist;

template <typename>
struct typelist_biggest;

template <typename First>
struct typelist_biggest<typelist<First>>
{
	using result = First;
};

template <typename First, typename Second, typename... Rest>
struct typelist_biggest<typelist<First, Second, Rest...>>
{
	using temp = std::conditional_t<(sizeof(First) > sizeof(Second)), First, Second>;
	using result = typename typelist_biggest<typelist<temp, Rest...>>::result;
};

template <typename, typename>
struct typelist_prepend;

template <typename... Types, typename New>
struct typelist_prepend<typelist<Types...>, New>
{
	using result = typelist<New, Types...>;
};

template <typename, typename>
struct typelist_remove_one;

template <typename Head, typename... Tail, typename Remove>
struct typelist_remove_one<typelist<Head, Tail...>, Remove>
{
	using removed = typename typelist_remove_one<typelist<Tail...>, Remove>::result;
	using result = typename typelist_prepend<removed, Head>::result;
};

template <typename... Tail, typename Remove>
struct typelist_remove_one<typelist<Remove, Tail...>, Remove>
{
	using result = typelist<Tail...>; // Do not keep removing recursively
};

template <typename, typename>
struct typelist_append;

template <typename... Types, typename New>
struct typelist_append<typelist<Types...>, New>
{
	using result = typelist<Types..., New>;
};

template <typename Remaining, typename Sorted = typelist<>>
struct typelist_sort
{
	// TODO: Implement me
	//	1. Find the biggest type in Remaining
	using biggest = typename typelist_biggest<Remaining>::result;
	//  2. Remove that type from Remaining to form NewRemaining
	using new_remaining = typename typelist_remove_one<Remaining, biggest>::result;
	//	3. Add that type to Sorted to form NewSorted
	using new_sorted = typename typelist_prepend<Sorted, biggest>::result;
	//	4. Return the recursive result from sorting NewRemaining, NewSorted
	using result = typename typelist_sort<new_remaining, new_sorted>::result;
};

template <typename Sorted>
struct typelist_sort<typelist<>, Sorted>
{
	using result = Sorted;	// Nothing left to sort
};

template <typename Typelist>
using typelist_sort_t = typename typelist_sort<Typelist>::result;

int main()
{
	using sfcd = typelist<std::string, float, char, double>;
	using sfcd_sorted = typelist<char, float, double, std::string>;
	static_assert(std::is_same_v<typelist_sort_t<sfcd>, sfcd_sorted>, "typelist_sort failed");

	using iiss = typelist<int, int, short, short>;
	using iiss_sorted = typelist<short, short, int, int>;
	static_assert(std::is_same_v<typelist_sort_t<iiss>, iiss_sorted>, "typelist_sort failed with duplicates");
}