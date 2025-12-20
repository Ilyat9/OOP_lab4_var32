#include "../include/Octagon.h"
#include <numbers>

template<Scalar T>
Octagon<T>::Octagon(const Point<T>& center, T radius) {
    if (radius <= 0) return;
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * std::numbers::pi * i / 8;
        T x = center.getX() + radius * static_cast<T>(std::cos(angle));
        T y = center.getY() + radius * static_cast<T>(std::sin(angle));
        this->vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}

template<Scalar T>
Octagon<T>::Octagon(const Octagon& other) {
    for (const auto& v : other.vertices) {
        this->vertices.push_back(std::make_unique<Point<T>>(*v));
    }
}

template<Scalar T>
double Octagon<T>::area() const {
    if (this->vertices.size() != 8) return 0.0;
    T side = distance(*this->vertices[0], *this->vertices[1]);
    return 2 * (1 + std::sqrt(2.0)) * side * side;
}

template<Scalar T>
Point<T> Octagon<T>::geometricCenter() const {
    T sumX = 0, sumY = 0;
    for (const auto& v : this->vertices) {
        sumX += v->getX();
        sumY += v->getY();
    }
    return Point<T>(sumX / this->vertices.size(), sumY / this->vertices.size());
}

template<Scalar T>
bool Octagon<T>::isValid() const {
    if (this->vertices.size() != 8) return false;
    Point<T> center = geometricCenter();
    T radius = distance(center, *this->vertices[0]);
    constexpr T eps = std::numeric_limits<T>::epsilon() * 100;
    for (const auto& v : this->vertices) {
        if (std::abs(distance(center, *v) - radius) > eps) return false;
    }
    return Figure<T>::isValid();
}

template<Scalar T>
Octagon<T>& Octagon<T>::operator=(const Octagon& other) {
    if (this != &other) {
        this->vertices.clear();
        for (const auto& v : other.vertices) {
            this->vertices.push_back(std::make_unique<Point<T>>(*v));
        }
    }
    return *this;
}

template class Octagon<int>;
template class Octagon<float>;
template class Octagon<double>;
