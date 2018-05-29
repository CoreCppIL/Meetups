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

namespace std3_ {

struct JsonArray;
struct JsonObject;

using JsonValue = std::variant<nullptr_t,                  // null
                               int,                        // number
                               std::string,                // string
                               bool,                       // boolean
                               std::shared_ptr<JsonArray>, // array
                               std::shared_ptr<JsonObject> // object
                               >;

template <typename T, typename... Args>
std::vector<T> make_vector(Args &&... args) {
  std::vector<T> res;
  (res.emplace_back(std::forward<Args>(args)), ...);
  return res;
}

struct JsonArray {
  std::vector<JsonValue> array;

  JsonArray(std::initializer_list<JsonValue> il) : array(il) {}
};

struct JsonObject {
  std::vector<std::pair<std::string, JsonValue>> object;

  JsonObject(std::initializer_list<std::pair<std::string, JsonValue>> il)
      : object(il) {}
};

std::ostream &operator<<(std::ostream &ost, const JsonValue &json) {
  std::visit(overload([&ost](const nullptr_t &) { ost << "null"; },
                      [&ost](const std::shared_ptr<JsonArray> &value) {
                        // should we check for null ptr?
                        ost << "[\n";
                        std::copy(begin(value->array), end(value->array),
                                  std::ostream_iterator<JsonValue>(ost, ",\n"));
                        ost << ']';
                      },
                      [&ost](const std::shared_ptr<JsonObject> &value) {
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

  using jo = std::initializer_list<std::pair<std::string, JsonValue>>;
  using ja = std::initializer_list<JsonValue>;
  return std::make_shared<JsonObject>(
    jo{ {"firstName"s, "John"s}, {"lastName"s, "Smith"s}, {"isAlive"s, true},
    {"age"s, 27},
    {
      "address"s,
      std::make_shared<JsonObject>(jo{
        {"streetAddress"s, "21 2nd Street"s},
        {"city"s, "New York"s}})
    },
    {
        "phoneNumbers"s,
        std::make_shared<JsonArray>(ja{
            std::make_shared<JsonObject>(jo{{"type"s, "home"s},
                                         {"number"s, "212 555-1234"s}}),
            std::make_shared<JsonObject>(jo{{"type"s, "office"s},
                                         {"number"s, "646 555-4567"s}})}),
    },
    {"spouse"s, nullptr} });
}

} // namespace std3_
