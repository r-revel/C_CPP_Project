#include "point.h"
#include <stdexcept>

namespace geometry
{

  double Point::distanceTo(const Point &other) const noexcept
  {
    const double dx = x_ - other.x_;
    const double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
  }

  Point Point::rotate90Clockwise() const noexcept
  {
    return Point(y_, -x_);
  }

  Point Point::operator+(const Point &other) const noexcept
  {
    return Point(x_ + other.x_, y_ + other.y_);
  }

  Point Point::operator-(const Point &other) const noexcept
  {
    return Point(x_ - other.x_, y_ - other.y_);
  }

  Point Point::operator/(double divisor) const
  {
    if (divisor == 0.0)
    {
      throw std::invalid_argument("Деление на ноль");
    }
    return Point(x_ / divisor, y_ / divisor);
  }

  std::istream &operator>>(std::istream &is, Point &point)
  {
    is >> point.x_ >> point.y_;
    return is;
  }

  std::ostream &operator<<(std::ostream &os, const Point &point)
  {
    os << "(" << point.x_ << ", " << point.y_ << ")";
    return os;
  }

}