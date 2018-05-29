#include <variant>
#include <iostream>
#include <string>

using Var = std::variant<int, std::string>;

Var duplicate(const Var& v) {
  struct Duplicater {
    Var operator()(int i) { return i * 2; }
    Var operator()(const std::string &s) { 
      return s + s; 
    }
  };
  return std::visit(Duplicater{}, v);
}

int main() {
  std::variant<int, std::string> v;

  v = 42;
  std::cout << std::get<int>(v) << '\n'; // prints 42

  try {
    std::cout << std::get<std::string>(v) << '\n'; // throws
  }
  catch (const std::bad_variant_access &e) {
    std::cout << e.what() << '\n'; // prints 'bad variant access'
  }

  // std::cout << std::get<long>(v) << '\n'; // doesn't compile

  v = "forty two";
  std::cout << std::get<std::string>(v) << '\n'; // prints 'forty two'

  v = duplicate(v);
  if (auto p = std::get_if<std::string>(&v)) {
    std::cout << "we have a string: " << *p << '\n'; // prints 'we have a string: forty twoforty two'
  }
  else {
    std::cout << "we don't have a string\n";
  }
}