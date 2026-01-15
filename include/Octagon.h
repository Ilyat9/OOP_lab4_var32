#pragma once
#include "Figure.h"
#include <cmath>

template<Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon(const Point<T>& center, T side_len);
    Octagon(const Octagon& other);
    
    double area() const override;
    Point<T> geometricCenter() const override;
    std::string getName() const override { return "Octagon"; }
    bool isValid() const override;

    void display(std::ostream& os) const override;
    
    Octagon& operator=(const Octagon& other);
};
