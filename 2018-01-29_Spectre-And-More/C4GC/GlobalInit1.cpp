// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i22-avoid-complex-initialization-of-global-objects
// example taken from
// https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL14-CPP.+Avoid+assumptions+about+the+initialization+order+between+translation+units
#include <cstring>

namespace global_init {
namespace bad {
// in file GlobalInit1.cpp
extern char const *const term;
bool isVT100 = strcmp(term, "VT100") == 0;
} // namespace bad

namespace good {
// in file GlobalInit1.cpp
extern char const *term();
bool isVT100() {
  static bool is = strcmp(term(), "VT100") == 0;
  return is;
}
} // namespace good
} // namespace global_init
