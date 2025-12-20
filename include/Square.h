#pragma once
#include "Figure.h"
#include <cmath>

template<Scalar T>
class Square : public Figure<T> {
public:
    Square(const Point<T>& center, T side);
    Square(const Square& other);
    
    double area() const override;
    Point<T> geometricCenter() const override;
    std::string getName() const override { return "Square"; }
    bool isValid() const override;
    
    Square& operator=(const Square& other);
};
