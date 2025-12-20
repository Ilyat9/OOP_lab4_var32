#include "../include/Square.h"

template<Scalar T>
Square<T>::Square(const Point<T>& center, T side) {
    T half = side / 2;
    this->vertices.push_back(std::make_unique<Point<T>>(center.getX() - half, center.getY() - half));
    this->vertices.push_back(std::make_unique<Point<T>>(center.getX() + half, center.getY() - half));
    this->vertices.push_back(std::make_unique<Point<T>>(center.getX() + half, center.getY() + half));
    this->vertices.push_back(std::make_unique<Point<T>>(center.getX() - half, center.getY() + half));
}

template<Scalar T>
Square<T>::Square(const Square& other) {
    for (const auto& vertex : other.vertices) {
        this->vertices.push_back(std::make_unique<Point<T>>(*vertex));
    }
}

template<Scalar T>
double Square<T>::area() const {
    if (this->vertices.size() < 2) return 0;
    
    T side = sqrt(pow(this->vertices[1]->getX() - this->vertices[0]->getX(), 2) +
                  pow(this->vertices[1]->getY() - this->vertices[0]->getY(), 2));
    return side * side;
}

template<Scalar T>
Point<T> Square<T>::geometricCenter() const {
    T sumX = 0, sumY = 0;
    for (const auto& vertex : this->vertices) {
        sumX += vertex->getX();
        sumY += vertex->getY();
    }
    return Point<T>(sumX / this->vertices.size(), sumY / this->vertices.size());
}

template<Scalar T>
Square<T>& Square<T>::operator=(const Square& other) {
    if (this != &other) {
        this->vertices.clear();
        for (const auto& vertex : other.vertices) {
            this->vertices.push_back(std::make_unique<Point<T>>(*vertex));
        }
    }
    return *this;
}

template<Scalar T>
bool Square<T>::isValid() const {
    if (this->vertices.size() != 4) return false;
    Point<T> center = geometricCenter();
    T radius = distance(center, *this->vertices[0]);
    constexpr T eps = std::numeric_limits<T>::epsilon() * 100;
    for (const auto& v : this->vertices) {
        if (std::abs(distance(center, *v) - radius) > eps) return false;
    }
    return Figure<T>::isValid();
}

template class Square<int>;
template class Square<float>;
template class Square<double>;
