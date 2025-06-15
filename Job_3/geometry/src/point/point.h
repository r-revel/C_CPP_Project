#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include <iostream>
#include <array>
#include <cmath>

namespace geometry
{

    class Point
    {
    private:
        double x_;
        double y_;

    public:
        Point() noexcept : x_(0.0), y_(0.0) {}
        Point(double x, double y) noexcept : x_(x), y_(y) {}

        explicit Point(const std::array<double, 2> &coords) noexcept : x_(coords[0]), y_(coords[1]) {}

        double getX() const noexcept { return x_; }
        double getY() const noexcept { return y_; }

        void setX(double x) noexcept { x_ = x; }
        void setY(double y) noexcept { y_ = y; }

        double distanceTo(const Point &other) const noexcept;

        Point rotate90Clockwise() const noexcept;

        Point operator+(const Point &other) const noexcept;
        Point operator-(const Point &other) const noexcept;
        Point operator/(double divisor) const;

        friend std::istream &operator>>(std::istream &is, Point &point);
        friend std::ostream &operator<<(std::ostream &os, const Point &point);
    };

}

#endif