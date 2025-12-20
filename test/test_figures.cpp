#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include <numbers>
#include <sstream>
#include <limits>

#include "../include/Array.h"
#include "../include/Point.h"
#include "../include/Figure.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include "../include/Square.h"

bool almostEqual(double a, double b, double eps = 1e-6) {
    return std::abs(a - b) < eps;
}

TEST(PointTest, ConstructionAndAccess) {
    Point<double> p(3.5, -2.0);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), -2.0);
}

TEST(PointTest, Equality) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 3.0);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, Distance) {
    Point<double> a(0, 0);
    Point<double> b(3, 4);
    EXPECT_DOUBLE_EQ(distance(a, b), 5.0);
}

TEST(OctagonTest, ConstructionAndVerticesCount) {
    auto oct = std::make_shared<Octagon<double>>(Point<double>(0, 0), 5.0);
    const auto& vertices = oct->getVertices();
    EXPECT_EQ(vertices.size(), 8);
    EXPECT_TRUE(oct->isValid());
}

TEST(OctagonTest, GeometricCenter) {
    Point<double> center(10, 20);
    auto oct = std::make_shared<Octagon<double>>(center, 3.0);
    Point<double> gc = oct->geometricCenter();
    EXPECT_DOUBLE_EQ(gc.getX(), 10.0);
    EXPECT_DOUBLE_EQ(gc.getY(), 20.0);
}

TEST(OctagonTest, AreaCalculation) {
    auto oct = std::make_shared<Octagon<double>>(Point<double>(0, 0), 1.0);
    EXPECT_NEAR(oct->area(), 2.828427, 1e-4);
}

TEST(OctagonTest, Validity) {
    auto oct = std::make_shared<Octagon<double>>(Point<double>(0, 0), 5.0);
    EXPECT_TRUE(oct->isValid());
}

TEST(TriangleTest, ConstructionAndVertices) {
    auto tri = std::make_shared<Triangle<double>>(Point<double>(0, 0), 4.0);
    const auto& vertices = tri->getVertices();
    EXPECT_EQ(vertices.size(), 3);
    EXPECT_TRUE(tri->isValid());
}

TEST(TriangleTest, GeometricCenter) {
    Point<double> center(5, -3);
    auto tri = std::make_shared<Triangle<double>>(center, 10.0);
    Point<double> gc = tri->geometricCenter();
    EXPECT_TRUE(almostEqual(gc.getX(), 5.0));
    EXPECT_TRUE(almostEqual(gc.getY(), -3.0));
}

TEST(SquareTest, ConstructionBySide) {
    auto sq = std::make_shared<Square<double>>(Point<double>(0, 0), 4.0);
    const auto& vertices = sq->getVertices();
    EXPECT_EQ(vertices.size(), 4);
    EXPECT_TRUE(sq->isValid());
    EXPECT_DOUBLE_EQ(sq->area(), 16.0);
}

TEST(SquareTest, VerticesPositions) {
    Point<double> center(1, 1);
    auto sq = std::make_shared<Square<double>>(center, 2.0);

    const auto& verts = sq->getVertices();

    EXPECT_TRUE(almostEqual(verts[0]->getX(), 0.0));
    EXPECT_TRUE(almostEqual(verts[0]->getY(), 0.0));
    EXPECT_TRUE(almostEqual(verts[1]->getX(), 2.0));
    EXPECT_TRUE(almostEqual(verts[1]->getY(), 0.0));
    EXPECT_TRUE(almostEqual(verts[2]->getX(), 2.0));
    EXPECT_TRUE(almostEqual(verts[2]->getY(), 2.0));
    EXPECT_TRUE(almostEqual(verts[3]->getX(), 0.0));
    EXPECT_TRUE(almostEqual(verts[3]->getY(), 2.0));
}

TEST(ArrayTest, PushBackAndSize) {
    Array<std::shared_ptr<Figure<double>>> arr;

    arr.push_back(std::make_shared<Octagon<double>>(Point<double>(0,0), 1.0));
    arr.push_back(std::make_shared<Triangle<double>>(Point<double>(0,0), 1.0));
    arr.push_back(std::make_shared<Square<double>>(Point<double>(0,0), 2.0));

    EXPECT_EQ(arr.getSize(), 3);
}

TEST(ArrayTest, Indexing) {
    Array<std::shared_ptr<Figure<double>>> arr;
    auto oct = std::make_shared<Octagon<double>>(Point<double>(0,0), 5.0);
    arr.push_back(oct);

    EXPECT_EQ(arr[0], oct);
    EXPECT_TRUE(almostEqual(arr[0]->area(), oct->area()));
}

TEST(ArrayTest, RemoveByIndex) {
    Array<std::shared_ptr<Figure<double>>> arr;

    auto f1 = std::make_shared<Square<double>>(Point<double>(0,0), 2.0);
    auto f2 = std::make_shared<Triangle<double>>(Point<double>(0,0), 1.0);
    auto f3 = std::make_shared<Octagon<double>>(Point<double>(0,0), 1.0);

    arr.push_back(f1);
    arr.push_back(f2);
    arr.push_back(f3);

    arr.remove(1);

    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], f1);
    EXPECT_EQ(arr[1], f3);
}

TEST(OutputTest, OperatorStream) {
    auto oct = std::make_shared<Octagon<double>>(Point<double>(0,0), 1.0);

    std::ostringstream oss;
    oss << *oct;

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Octagon") != std::string::npos);
    EXPECT_TRUE(output.find("Center") != std::string::npos);
    EXPECT_TRUE(output.find("Area") != std::string::npos);
}
