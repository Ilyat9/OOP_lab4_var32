#pragma once
#include "Point.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <limits>

template<Scalar T>
class Figure {
protected:
    using PointPtr = std::unique_ptr<Point<T>>;
    std::vector<PointPtr> vertices;

public:
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual Point<T> geometricCenter() const = 0;
    virtual std::string getName() const = 0;

    // Новая функция: проверка правильности фигуры
    virtual bool isValid() const {
        if (vertices.size() < 3) return false;
        // Проверка на совпадение вершин
        for (size_t i = 0; i < vertices.size(); ++i) {
            for (size_t j = i + 1; j < vertices.size(); ++j) {
                if (*vertices[i] == *vertices[j]) return false;
            }
        }
        return true;
    }

    const std::vector<PointPtr>& getVertices() const { return vertices; }

    virtual operator double() const {
        return area();
    }

    bool operator==(const Figure& other) const {
        if (vertices.size() != other.vertices.size()) return false;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (!(*vertices[i] == *other.vertices[i])) return false;
        }
        return true;
    }

    virtual void print(std::ostream& os) const {
        os << getName() << ": ";
        for (const auto& vertex : vertices) {
            os << *vertex << " ";
        }
        os << "Center: " << geometricCenter() << ", Area: " << area();
        if (!isValid()) os << " [INVALID FIGURE]";
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.print(os);
        return os;
    }
};
