#pragma once
#include "Figure.h"
#include <cmath>

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle(const Point<T>& center, T radius);
    Triangle(const Triangle& other);
    
    double area() const override;
    Point<T> geometricCenter() const override;
    std::string getName() const override { return "Triangle"; }
    bool isValid() const override;
    
    Triangle& operator=(const Triangle& other);
};
