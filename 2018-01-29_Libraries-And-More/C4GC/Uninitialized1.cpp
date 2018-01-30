// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es20-always-initialize-an-object

namespace uninitialized {

namespace bad {

int foo(int val) {
  int i;
  if (val > 0) {
    i = 2;
  }
  return i;
}

} // namespace bad

namespace good {

int foo(int val) {
  int i = 0;
  if (val > 0) {
    i = 2;
  }
  return i;
}
} // namespace good

} // namespace uninitialized
