#include "../src/figure/figure.h"
#include <gtest/gtest.h>

namespace geometry {

TEST(FigureTest, DefaultConstructor) {
    Figure f;
    EXPECT_EQ(f.getVertexCount(), 0);
}

TEST(FigureTest, SingleVertexConstructor) {
    Point p(1, 2);
    Figure f(p);
    EXPECT_EQ(f.getVertexCount(), 1);
    EXPECT_DOUBLE_EQ(f[0].getX(), 1.0);
    EXPECT_DOUBLE_EQ(f[0].getY(), 2.0);
}

TEST(FigureTest, ArrayConstructor) {
    Point points[] = {{1, 2}, {3, 4}, {5, 6}};
    Figure f(3, points);
    EXPECT_EQ(f.getVertexCount(), 3);
    EXPECT_DOUBLE_EQ(f[1].getX(), 3.0);
    EXPECT_DOUBLE_EQ(f[1].getY(), 4.0);
}

TEST(FigureTest, CopyConstructor) {
    Point points[] = {{1, 2}, {3, 4}};
    Figure f1(2, points);
    Figure f2(f1);
    
    EXPECT_EQ(f2.getVertexCount(), 2);
    EXPECT_DOUBLE_EQ(f2[0].getX(), 1.0);
    EXPECT_DOUBLE_EQ(f2[1].getY(), 4.0);
}

TEST(FigureTest, MoveConstructor) {
    Point points[] = {{1, 2}, {3, 4}};
    Figure f1(2, points);
    Figure f2(std::move(f1));
    
    EXPECT_EQ(f2.getVertexCount(), 2);
    EXPECT_EQ(f1.getVertexCount(), 0);
}

TEST(FigureTest, AssignmentOperators) {
    Point points[] = {{1, 2}, {3, 4}};
    Figure f1(2, points);
    Figure f2;
    
    // Copy assignment
    f2 = f1;
    EXPECT_EQ(f2.getVertexCount(), 2);
    
    // Move assignment
    Figure f3;
    f3 = std::move(f2);
    EXPECT_EQ(f3.getVertexCount(), 2);
    EXPECT_EQ(f2.getVertexCount(), 0);
}

TEST(FigureTest, AddVertex) {
    Figure f;
    f.addVertex(Point(1, 2));
    f.addVertex(Point(3, 4));
    
    EXPECT_EQ(f.getVertexCount(), 2);
    EXPECT_DOUBLE_EQ(f[1].getX(), 3.0);
}

TEST(FigureTest, IndexOperator) {
    Point points[] = {{1, 2}, {3, 4}};
    Figure f(2, points);
    
    EXPECT_DOUBLE_EQ(f[0].getX(), 1.0);
    EXPECT_DOUBLE_EQ(f[1].getY(), 4.0);
    EXPECT_THROW(f[2], std::out_of_range);
}

TEST(FigureTest, PlusEqualOperator) {
    Figure f;
    f += Point(1, 2);
    f += Point(3, 4);
    
    EXPECT_EQ(f.getVertexCount(), 2);
    EXPECT_DOUBLE_EQ(f[1].getX(), 3.0);
}

TEST(FigureTest, Rotation) {
    Point points[] = {{1, 0}, {0, 1}};
    Figure f(2, points);
    
    // Rotate 90 degrees counter-clockwise around origin
    f.rotate(Point(0, 0), 90);
    
    EXPECT_NEAR(f[0].getX(), 0.0, 1e-9);
    EXPECT_NEAR(f[0].getY(), 1.0, 1e-9);
    EXPECT_NEAR(f[1].getX(), -1.0, 1e-9);
    EXPECT_NEAR(f[1].getY(), 0.0, 1e-9);
}

TEST(FigureTest, InvalidRotationAngle) {
    Point p(1, 1);
    Figure f(p);
    EXPECT_THROW(f.rotate(Point(0, 0), 45), std::invalid_argument);
}

TEST(FigureTest, IOStreamOperators) {
    Point points[] = {{1, 2}, {3, 4}};
    Figure f1(2, points);
    
    std::ostringstream oss;
    oss << f1;
    EXPECT_TRUE(oss.str().find("Figure with 2 vertices") != std::string::npos);
    
    std::istringstream iss("2 1 2 3 4");
    Figure f2;
    iss >> f2;
    
    EXPECT_EQ(f2.getVertexCount(), 2);
    EXPECT_DOUBLE_EQ(f2[1].getX(), 3.0);
}

} // namespace geometry