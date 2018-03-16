// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c49-prefer-initialization-to-assignment-in-constructors
#include <string>

namespace member_init {

namespace bad {
class B {
  std::string s1;

public:
  B(const std::string &name) { s1 = "Hello, " + name; }
};

class X {
  int i;
  std::string s;
  int j;

public:
  X() : i{666}, s{"qqq"} {}
  X(int ii) : i{ii} {}
};

} // namespace bad

namespace good {
class B {
  std::string s1;

public:
  B(const std::string &name) : s1{"Hello, " + name} {}
};

class X {
  int i{666};
  std::string s{"qqq"};
  int j{0};

public:
  X() = default;
  X(int ii) : i{ii} {}
};
} // namespace good

} // namespace member_init
