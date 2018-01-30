// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#con4-use-const-to-define-objects-with-values-that-do-not-change-after-construction
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es28-use-lambdas-for-complex-initialization-especially-of-const-variables

namespace complex_init {

struct widget {
  void operator+=(int /*unused*/) {}
};

struct obj {
  int do_something_with(int i) const { return i; }
};

namespace bad {

void foo() {
  const obj some_obj{};
  const auto N = 100;
  widget x{};
  for (auto i = 2; i <= N; ++i) {
    x += some_obj.do_something_with(i);
  }
}

} // namespace bad

namespace good {

void foo() {
  const obj some_obj{};
  const auto N = 100;
  const widget x = [&] {
    widget val{};
    for (auto i = 2; i <= N; ++i) {
      val += some_obj.do_something_with(i);
    }
    return val;
  }();
}

} // namespace good

} // namespace complex_init
