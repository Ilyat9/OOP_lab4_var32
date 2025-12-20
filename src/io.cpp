#include <iostream>
#include <memory>
#include <typeinfo>
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include "../include/Square.h"
#include "../include/Array.h"

template<Scalar T>
std::unique_ptr<Figure<T>> createFigure(int type) {
    std::cout << "Enter center coordinates (x y): ";
    T x, y;
    std::cin >> x >> y;
    Point<T> center(x, y);
    
    std::cout << "Enter size parameter: ";
    T param;
    std::cin >> param;
    
    switch(type) {
        case 1: // Octagon
            return std::make_unique<Octagon<T>>(center, param);
        case 2: // Triangle
            return std::make_unique<Triangle<T>>(center, param);
        case 3: // Square
            return std::make_unique<Square<T>>(center, param);
        default:
            return nullptr;
    }
}

template<Scalar T>
void printAllGeometricCenters(const Array<std::shared_ptr<Figure<T>>>& array) {
    std::cout << "\nGeometric centers:\n";
    for (size_t i = 0; i < array.getSize(); ++i) {
        std::cout << i << ": " << array[i]->geometricCenter() << std::endl;
    }
}

template<Scalar T>
void printAllVertices(const Array<std::shared_ptr<Figure<T>>>& array) {
    std::cout << "\nVertices of all figures:\n";
    for (size_t i = 0; i < array.getSize(); ++i) {
        std::cout << i << ": ";
        for (const auto& vertex : array[i]->getVertices()) {
            std::cout << *vertex << " ";
        }
        std::cout << std::endl;
    }
}

template<Scalar T>
void printAllAreas(const Array<std::shared_ptr<Figure<T>>>& array) {
    std::cout << "\nAreas of all figures:\n";
    for (size_t i = 0; i < array.getSize(); ++i) {
        std::cout << i << ": " << array[i]->area() << std::endl;
    }
}

template<Scalar T>
double calculateTotalArea(const Array<std::shared_ptr<Figure<T>>>& array) {
    double total = 0;
    for (size_t i = 0; i < array.getSize(); ++i) {
        total += static_cast<double>(*array[i]);
    }
    return total;
}

// Явные инстанцирования
template std::unique_ptr<Figure<int>> createFigure<int>(int);
template std::unique_ptr<Figure<double>> createFigure<double>(int);
template std::unique_ptr<Figure<float>> createFigure<float>(int);

template void printAllGeometricCenters<int>(const Array<std::shared_ptr<Figure<int>>>&);
template void printAllGeometricCenters<double>(const Array<std::shared_ptr<Figure<double>>>&);
template void printAllGeometricCenters<float>(const Array<std::shared_ptr<Figure<float>>>&);

template void printAllVertices<int>(const Array<std::shared_ptr<Figure<int>>>&);
template void printAllVertices<double>(const Array<std::shared_ptr<Figure<double>>>&);
template void printAllVertices<float>(const Array<std::shared_ptr<Figure<float>>>&);

template void printAllAreas<int>(const Array<std::shared_ptr<Figure<int>>>&);
template void printAllAreas<double>(const Array<std::shared_ptr<Figure<double>>>&);
template void printAllAreas<float>(const Array<std::shared_ptr<Figure<float>>>&);

template double calculateTotalArea<int>(const Array<std::shared_ptr<Figure<int>>>&);
template double calculateTotalArea<double>(const Array<std::shared_ptr<Figure<double>>>&);
template double calculateTotalArea<float>(const Array<std::shared_ptr<Figure<float>>>&);
