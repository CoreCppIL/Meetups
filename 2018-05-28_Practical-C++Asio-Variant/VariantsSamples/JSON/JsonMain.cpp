#include "JsonBoost.h"
#include "JsonStd.h"
#include "JsonStd2.h"
#include "JsonStd3.h"
#include <sstream>

int main() {
  auto to_string = [](const auto &v) {
    std::stringstream sst;
    sst << v;
    return sst.str();
  };
  auto a = to_string(std_::construct());
  auto b = to_string(boost_::construct());
  auto c = to_string(std2_::construct());
  auto d = to_string(std3_::construct());
  assert(a == b);
  assert(b == c);
  assert(c == d);
}