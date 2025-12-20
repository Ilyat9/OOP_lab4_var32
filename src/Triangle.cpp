#include "../include/Triangle.h"

template<Scalar T>
Triangle<T>::Triangle(const Point<T>& center, T radius) {
    for (int i = 0; i < 3; ++i) {
        double angle = 2 * M_PI * i / 3;
        T x = center.getX() + radius * static_cast<T>(cos(angle));
        T y = center.getY() + radius * static_cast<T>(sin(angle));
        this->vertices.push_back(std::make_unique<Point<T>>(x, y));
    }
}

template<Scalar T>
Triangle<T>::Triangle(const Triangle& other) {
    for (const auto& vertex : other.vertices) {
        this->vertices.push_back(std::make_unique<Point<T>>(*vertex));
    }
}

template<Scalar T>
double Triangle<T>::area() const {
    if (this->vertices.size() < 3) return 0;
    
    T x1 = this->vertices[0]->getX();
    T y1 = this->vertices[0]->getY();
    T x2 = this->vertices[1]->getX();
    T y2 = this->vertices[1]->getY();
    T x3 = this->vertices[2]->getX();
    T y3 = this->vertices[2]->getY();
    
    return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}

template<Scalar T>
Point<T> Triangle<T>::geometricCenter() const {
    T sumX = 0, sumY = 0;
    for (const auto& vertex : this->vertices) {
        sumX += vertex->getX();
        sumY += vertex->getY();
    }
    return Point<T>(sumX / this->vertices.size(), sumY / this->vertices.size());
}

template<Scalar T>
Triangle<T>& Triangle<T>::operator=(const Triangle& other) {
    if (this != &other) {
        this->vertices.clear();
        for (const auto& vertex : other.vertices) {
            this->vertices.push_back(std::make_unique<Point<T>>(*vertex));
        }
    }
    return *this;
}

template<Scalar T>
bool Triangle<T>::isValid() const {
    if (this->vertices.size() != 3) return false;
    Point<T> center = geometricCenter();
    T radius = distance(center, *this->vertices[0]);
    constexpr T eps = std::numeric_limits<T>::epsilon() * 100;
    for (const auto& v : this->vertices) {
        if (std::abs(distance(center, *v) - radius) > eps) return false;
    }
    return Figure<T>::isValid();
}

template class Triangle<int>;
template class Triangle<float>;
template class Triangle<double>;
