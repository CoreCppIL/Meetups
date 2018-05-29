#pragma once

#include "../overload.h"
#include <algorithm>
#include <array>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

namespace std_ {

#if 0
using JsonValue =
    std::variant<nullptr_t,                                     // null
                 int,                                           // number
                 std::string,                                   // string
                 bool,                                          // boolean
                 std::vector<JsonValue>,                        // array
                 std::vector<std::pair<std::string, JsonValue>> // object
                 >;
#endif

struct JsonArray;
struct JsonObject;

using JsonValue = std::variant<nullptr_t,                  // null
                               int,                        // number
                               std::string,                // string
                               bool,                       // boolean
                               std::unique_ptr<JsonArray>, // array
                               std::unique_ptr<JsonObject> // object
                               >;

template <typename T, typename... Args>
std::vector<T> make_vector(Args &&... args) {
  std::vector<T> res;
  (res.emplace_back(std::forward<Args>(args)), ...);
  return res;
}

struct JsonArray {
  std::vector<JsonValue> array;

  template <typename... Args>
  JsonArray(Args &&... args)
      : array(make_vector<JsonValue>(std::forward<Args>(args)...)) {}
};

struct JsonObject {
  std::vector<std::pair<std::string, JsonValue>> object;

  template <typename... Args>
  JsonObject(Args &&... args)
      : object(make_vector<std::pair<std::string, JsonValue>>(
            std::forward<Args>(args)...)) {}
};

std::ostream &operator<<(std::ostream &ost, const JsonValue &json) {
  std::visit(overload([&ost](const nullptr_t &) { ost << "null"; },
                      [&ost](const std::unique_ptr<JsonArray> &value) {
                        // should we check for null ptr?
                        ost << "[\n";
                        std::copy(begin(value->array), end(value->array),
                                  std::ostream_iterator<JsonValue>(ost, ",\n"));
                        ost << ']';
                      },
                      [&ost](const std::unique_ptr<JsonObject> &value) {
                        // should we check for null ptr?
                        ost << "{\n";
                        std::for_each(begin(value->object), end(value->object),
                                      [&](const auto &p) {
                                        ost << p.first << ": " << p.second
                                            << ",\n";
                                      });
                        ost << '}';
                      },
                      [&ost](const auto &value) { ost << value; }),
             json);
  return ost;
}

JsonValue construct() {
  using namespace std::string_literals;

  using p = std::pair<std::string, JsonValue>;
  return std::make_unique<JsonObject>(
      p{"firstName"s, "John"s}, p{"lastName"s, "Smith"s}, p{"isAlive"s, true},
      p{"age"s, 27},
      p{"address"s,
        std::make_unique<JsonObject>(p{"streetAddress"s, "21 2nd Street"s},
                                     p{"city"s, "New York"s})},
      p{
          "phoneNumbers"s,
          std::make_unique<JsonArray>(
              std::make_unique<JsonObject>(p{"type"s, "home"s},
                                           p{"number"s, "212 555-1234"s}),
              std::make_unique<JsonObject>(p{"type"s, "office"s},
                                           p{"number"s, "646 555-4567"s})),
      },
      p{"spouse"s, nullptr});
}

} // namespace std_
