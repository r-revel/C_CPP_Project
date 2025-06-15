#include "../src/point/point.h"
#include <gtest/gtest.h>

namespace geometry {

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_DOUBLE_EQ(p.getX(), 0.0);
    EXPECT_DOUBLE_EQ(p.getY(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3.5, -2.1);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), -2.1);
}

TEST(PointTest, ArrayConstructor) {
    std::array<double, 2> coords = {1.2, 3.4};
    Point p(coords);
    EXPECT_DOUBLE_EQ(p.getX(), 1.2);
    EXPECT_DOUBLE_EQ(p.getY(), 3.4);
}

TEST(PointTest, DistanceCalculation) {
    Point p1(0, 0);
    Point p2(3, 4);
    EXPECT_DOUBLE_EQ(p1.distanceTo(p2), 5.0);
}

TEST(PointTest, AdditionOperator) {
    Point p1(1, 2);
    Point p2(3, 4);
    Point result = p1 + p2;
    EXPECT_DOUBLE_EQ(result.getX(), 4.0);
    EXPECT_DOUBLE_EQ(result.getY(), 6.0);
}

TEST(PointTest, SubtractionOperator) {
    Point p1(5, 6);
    Point p2(2, 3);
    Point result = p1 - p2;
    EXPECT_DOUBLE_EQ(result.getX(), 3.0);
    EXPECT_DOUBLE_EQ(result.getY(), 3.0);
}

TEST(PointTest, DivisionOperator) {
    Point p(6, 9);
    Point result = p / 3;
    EXPECT_DOUBLE_EQ(result.getX(), 2.0);
    EXPECT_DOUBLE_EQ(result.getY(), 3.0);
}

TEST(PointTest, DivisionByZero) {
    Point p(1, 1);
    EXPECT_THROW(p / 0, std::invalid_argument);
}

TEST(PointTest, Rotate90Clockwise) {
    Point p(1, 0);
    Point rotated = p.rotate90Clockwise();
    EXPECT_DOUBLE_EQ(rotated.getX(), 0.0);
    EXPECT_DOUBLE_EQ(rotated.getY(), -1.0);
}

TEST(PointTest, IOStreamOperators) {
    Point p(1.5, -2.5);
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(1.5, -2.5)");

    std::istringstream iss("3.14 6.28");
    Point p2;
    iss >> p2;
    EXPECT_DOUBLE_EQ(p2.getX(), 3.14);
    EXPECT_DOUBLE_EQ(p2.getY(), 6.28);
}

} // namespace geometry