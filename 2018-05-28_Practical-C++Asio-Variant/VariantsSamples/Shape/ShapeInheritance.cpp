#include <iostream>
#include <memory>
#include <numeric>

struct Shape {
  virtual double area() const = 0;
  virtual ~Shape() = default;
};

struct Square final : Shape {
  explicit Square(double length) : length{ length } {}
  double area() const override { return length * length; }
  double length;
};

struct Circle final : Shape {
  explicit Circle(double radius) : radius{ radius } {}
  double area() const override {
    constexpr double PI = 3.141592653589793238463;
    return PI * radius * radius;
  }
  double radius;
};

int main() {
  const std::unique_ptr<Shape> shapes[] = {std::make_unique<Square>(4),
                                           std::make_unique<Circle>(2)};

  const auto areaSum =
      std::accumulate(std::begin(shapes), std::end(shapes), 0.0,
                      [](double current, const std::unique_ptr<Shape> &shape) {
                        return current + shape->area();
                      });

  std::cout << "area sum = " << areaSum << '\n';
}
