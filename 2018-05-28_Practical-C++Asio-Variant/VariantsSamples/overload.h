#pragma once
#include <utility>

#if __cplusplus >= 201703L

template <typename... Funcs> struct overload_set : Funcs... {
  using Funcs::operator()...; // exposes operator() from every base
};

template <typename... Funcs>
overload_set(Funcs...)->overload_set<Funcs...>; // C++17 deduction guide

#else

template <typename...> struct overload_set {
  void operator()() {}
};

template <typename Func, typename... Funcs>
struct overload_set<Func, Funcs...> : Func, overload_set<Funcs...> {
  using Func::operator();
  using overload_set<Funcs...>::operator();

  overload_set(const Func &f, const Funcs &... fs)
      : Func(f), overload_set<Funcs...>(fs...) {}
};

#endif

template <typename... Funcs>
overload_set<Funcs...> overload(Funcs &&... funcs) {
  return {std::forward<Funcs>(funcs)...};
}
