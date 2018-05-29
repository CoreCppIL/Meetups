#pragma once

#include <algorithm>
#include <boost/variant.hpp>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <variant>
#include <vector>
#include "../overload.h"

namespace boost_ {

struct JsonArray;
struct JsonObject;

using JsonValue = boost::variant<nullptr_t, int, std::string, bool,
                                 boost::recursive_wrapper<JsonArray>,
                                 boost::recursive_wrapper<JsonObject>>;

struct JsonArray {
  std::vector<JsonValue> array;

  JsonArray(std::initializer_list<JsonValue> il)
      : array(il) {}
};

struct JsonObject {
  std::vector<std::pair<std::string, JsonValue>> object;

  JsonObject(std::initializer_list<std::pair<std::string, JsonValue>> il)
      : object(il) {}
};

std::ostream &operator<<(std::ostream &ost, const JsonValue &json) {
  boost::apply_visitor(overload([&ost](const nullptr_t &) { ost << "null"; },
                      [&ost](const JsonArray &value) {
                        ost << "[\n";
                        std::copy(begin(value.array), end(value.array),
                                  std::ostream_iterator<JsonValue>(ost, ",\n"));
                        ost << ']';
                      },
                      [&ost](const JsonObject &value) {
                        ost << "{\n";
                        std::for_each(
                            begin(value.object), end(value.object), [&](const auto &pair) {
                              ost << pair.first << ": " << pair.second << ",\n";
                            });
                        ost << '}';
                      },
                      [&ost](const auto &value) { ost << value; }),
             json);
  return ost;
}

JsonValue construct() {
  using namespace std::string_literals;
  return JsonObject{
      {"firstName"s, "John"s},
      {"lastName"s, "Smith"s},
      {"isAlive"s, true},
      {"age"s, 27},
      {"address"s, JsonObject{{"streetAddress"s, "21 2nd Street"s},
                              {"city"s, "New York"s}}},
      {
          "phoneNumbers"s,
          JsonArray{
              JsonObject{{"type"s, "home"s}, {"number"s, "212 555-1234"s}},
              JsonObject{{"type"s, "office"s}, {"number"s, "646 555-4567"s}}},
      },
      {"spouse"s, nullptr}};
}

} // namespace boost_
