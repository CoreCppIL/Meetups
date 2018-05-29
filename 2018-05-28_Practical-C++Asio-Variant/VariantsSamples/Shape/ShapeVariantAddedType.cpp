#include "overload.h"
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

struct Triangle {
  Triangle(double base, double height) : base{base}, height{height} {}
  double base, height;
};

using Shape = std::variant<Square, Circle, Triangle>;

double area(const Shape &shape) {
  return std::visit(
      overload(
          [](const Square &square) { return square.length * square.length; },
          [](const Circle &circle) {
            constexpr double PI = 3.141592653589793238463;
            return PI * circle.radius * circle.radius;
          },
          [](const Triangle &triangle) {
            return triangle.base * triangle.height / 2;
          }),
      shape);
}

int main() {
  const Shape shapes[] = {Square{4}, Circle{2}, Triangle{2, 3}};

  const auto areaSum = std::accumulate(
      std::begin(shapes), std::end(shapes), 0.0,
      [](double current, const Shape &shape) { return current + area(shape); });

  std::cout << "area sum = " << areaSum << '\n';
}
