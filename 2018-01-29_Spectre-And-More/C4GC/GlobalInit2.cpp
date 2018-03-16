// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i22-avoid-complex-initialization-of-global-objects
// example taken from
// https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL14-CPP.+Avoid+assumptions+about+the+initialization+order+between+translation+units
#include <cstdlib>

namespace global_init {
namespace bad {
// in file GlobalInit2.cpp
char const *const term = getenv("TERM");
} // namespace bad

namespace good {
// in file GlobalInit2.cpp
char const *term() {
  static char const *const theTerm = getenv("TERM");
  return theTerm;
}
} // namespace good
} // namespace global_init
