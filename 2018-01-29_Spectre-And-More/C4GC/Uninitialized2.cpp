// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es20-always-initialize-an-object
#include <string>

namespace uninitialized {
struct T1 {};
class T2 {
public:
  T2() {}
};

namespace bad {
int n;

void foo() {
  int n2;
  std::string s;
  T1 t1;
  T2 t2;
}
} // namespace bad

namespace good {
auto n = 0;

void foo() {
  auto n2 = 0;
  auto s = std::string{};
  auto t1 = T1{};
  auto t2 = T2{};
}
} // namespace good

} // namespace uninitialized
