#include <iostream>
#include <memory>
#include <limits>
#include "../include/Array.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include "../include/Square.h"
#include "../src/io.cpp"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;

    std::cout << "=== Система управления фигурами ===\n";

    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить восьмиугольник\n";
        std::cout << "2. Добавить треугольник\n";
        std::cout << "3. Добавить квадрат\n";
        std::cout << "4. Вывести все геометрические центры\n";
        std::cout << "5. Вывести все вершины фигур\n";
        std::cout << "6. Вывести все площади\n";
        std::cout << "7. Вычислить общую площадь\n";
        std::cout << "8. Удалить фигуру по индексу\n";
        std::cout << "9. Вывести все фигуры полностью\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        try {
            switch (choice) {
                case 1:
                case 2:
                case 3: {
                    auto fig = createFigure<double>(choice);
                    if (fig && fig->isValid()) {
                        figures.add_element(std::move(fig));
                        std::cout << "Фигура успешно добавлена!\n";
                    } else if (fig) {
                        std::cout << "Фигура создана, но не прошла проверку валидности.\n";
                    }
                    break;
                }
                case 4:
                    printAllGeometricCenters(figures);
                    break;
                case 5:
                    printAllVertices(figures);
                    break;
                case 6:
                    printAllAreas(figures);
                    break;
                case 7:
                    std::cout << "Общая площадь всех фигур: "
                              << calculateTotalArea(figures) << std::endl;
                    break;
                case 8: {
                    if (figures.length() == 0) {
                        std::cout << "Массив пуст!\n";
                        break;
                    }
                    std::cout << "Введите индекс фигуры для удаления (0-"
                              << figures.length() - 1 << "): ";
                    size_t index;
                    std::cin >> index;
                    if (index < figures.length()) {
                        figures.erase_at(index);
                        std::cout << "Фигура удалена.\n";
                    } else {
                        std::cout << "Неверный индекс!\n";
                    }
                    break;
                }
                case 9:
                    if (figures.length() == 0) {
                        std::cout << "Нет фигур для вывода.\n";
                    } else {
                        std::cout << "\nВсе фигуры:\n";
                        for (size_t i = 0; i < figures.length(); ++i) {
                            std::cout << i << ": " << *figures[i] << std::endl;
                        }
                    }
                    break;
                default:
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}
