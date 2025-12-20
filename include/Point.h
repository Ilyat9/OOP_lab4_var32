#pragma once
#include "concepts.h"
#include <limits>
#include <iostream>
#include <numbers>
#include <cmath>

template<Scalar T>
class Point {
private:
    T x, y;
    
public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    
    T getX() const { return x; }
    T getY() const { return y; }
    
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator/(T divisor) const {
        return Point(x / divisor, y / divisor);
    }
};

template<Scalar T>
T distance(const Point<T>& a, const Point<T>& b) {
    T dx = a.getX() - b.getX();
    T dy = a.getY() - b.getY();
    return std::sqrt(dx*dx + dy*dy);
}
