#pragma once
#include "Point.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Figure {
protected:
    using VertexPtr = std::unique_ptr<Point<T>>;
    std::vector<VertexPtr> _points; 

public:
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual Point<T> geometricCenter() const = 0;
    virtual std::string getName() const = 0;

    virtual bool isValid() const {
        if (_points.size() < 3) return false;
        
        for (size_t i = 0; i < _points.size(); ++i) {
            for (size_t j = i + 1; j < _points.size(); ++j) {
                if (*_points[i] == *_points[j]) return false;
            }
        }
        return true;
    }

    const std::vector<VertexPtr>& getVertices() const { return _points; }

    virtual operator double() const {
        return area();
    }

    bool operator==(const Figure& other) const {
        if (_points.size() != other._points.size()) return false;
        for (size_t i = 0; i < _points.size(); ++i) {
            if (!(*_points[i] == *other._points[i])) return false;
        }
        return true;
    }

    virtual void display(std::ostream& os) const {
        os << getName() << " | Vertices: ";
        for (const auto& v : _points) {
            os << *v << " ";
        }
        os << " | Center: " << geometricCenter() << " | Area: " << area();
        if (!isValid()) os << " (Warning: Geometry is Invalid)";
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.display(os);
        return os;
    }
};
