#include "overload.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <variant>

struct Square {
  explicit Square(double length) : length{length} {}
  double length;
};

struct Circle {
  explicit Circle(double radius) : radius{radius} {}
  double radius;
};

using Shape = std::variant<Square, Circle>;

double area(const Shape &shape) {
  return std::visit(
      overload(
          [](const Square &square) { return square.length * square.length; },
          [](const Circle &circle) {
            constexpr double PI = 3.141592653589793238463;
            return PI * circle.radius * circle.radius;
          }),
      shape);
}

double perimeter(const Shape &shape) {
  return std::visit(
      overload([](const Square &square) { return 4 * square.length; },
               [](const Circle &circle) {
                 constexpr double PI = 3.141592653589793238463;
                 return 2 * PI * circle.radius;
               }),
      shape);
}

int main() {
  const Shape shapes[] = {Square{4}, Circle{2}};

  const auto areaSum = std::accumulate(
      std::begin(shapes), std::end(shapes), 0.0,
      [](double current, const Shape &shape) { return current + area(shape); });

  std::cout << "area sum = " << areaSum << '\n';

  const auto maxPerimeter =
      std::accumulate(std::begin(shapes), std::end(shapes), 0.0,
                      [](double current, const Shape &shape) {
                        return std::max(current, perimeter(shape));
                      });

  std::cout << "perimeter max = " << maxPerimeter << '\n';
}
