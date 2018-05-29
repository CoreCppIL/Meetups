#pragma once

#include "../overload.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

#define REQUIRES(...) std::enable_if_t<(__VA_ARGS__), int> = 0

namespace std2_ {

struct JsonValue;

using JsonArray = std::vector<JsonValue>;
using JsonObject = std::vector<std::pair<std::string, JsonValue>>;

struct JsonValue {
  std::variant<nullptr_t,   // null
               int,         // number
               std::string, // string
               bool,        // boolean
               JsonArray,   // array
               JsonObject   // object
               >
      value;

  template <typename Arg, REQUIRES(!std::is_same_v<std::decay_t<Arg>, JsonValue>)>
  JsonValue(Arg &&arg) : value(std::forward<Arg>(arg)) {}
};

std::ostream &operator<<(std::ostream &ost, const JsonValue &json) {
  std::visit(overload([&ost](const nullptr_t &) { ost << "null"; },
                      [&ost](const JsonArray &value) {
                        ost << "[\n";
                        std::copy(begin(value), end(value),
                                  std::ostream_iterator<JsonValue>(ost, ",\n"));
                        ost << ']';
                      },
                      [&ost](const JsonObject &value) {
                        ost << "{\n";
                        std::for_each(
                            begin(value), end(value), [&](const auto &pair) {
                              ost << pair.first << ": " << pair.second << ",\n";
                            });
                        ost << '}';
                      },
                      [&ost](const auto &value) { ost << value; }),
             json.value);
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

} // namespace std2_
