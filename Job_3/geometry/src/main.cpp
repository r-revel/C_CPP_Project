#include "./point/point.h"
#include "./figure/figure.h"
#include <iostream>
#include <limits>

using namespace geometry;

// Очистка буфера ввода
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Тестирование операций с точками
void testPointOperations() {
    std::cout << "=== Тестирование операций с точками ===\n";
    
    Point p1, p2;
    std::cout << "Введите координаты точки 1 (x y): ";
    std::cin >> p1;
    std::cout << "Введите координаты точки 2 (x y): ";
    std::cin >> p2;
    
    std::cout << "Точка 1: " << p1 << "\n";
    std::cout << "Точка 2: " << p2 << "\n";
    std::cout << "Расстояние между точками: " << p1.distanceTo(p2) << "\n";
    std::cout << "Сумма: " << p1 + p2 << "\n";
    std::cout << "Разность: " << p1 - p2 << "\n";
    
    try {
        double divisor;
        std::cout << "Введите делитель для деления точки: ";
        std::cin >> divisor;
        std::cout << "Точка 1, делённая на " << divisor << ": " << p1 / divisor << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
    
    std::cout << "Точка 1, повёрнутая на 90° по часовой стрелке: " << p1.rotate90Clockwise() << "\n";
}

// Тестирование операций с фигурами
void testFigureOperations() {
    std::cout << "\n=== Тестирование операций с фигурами ===\n";
    
    Figure figure;
    size_t choice;
    
    while (true) {
        std::cout << "\nТекущая фигура: " << figure << "\n";
        std::cout << "1. Добавить вершину\n";
        std::cout << "2. Получить вершину по индексу\n";
        std::cout << "3. Повернуть фигуру\n";
        std::cout << "0. Вернуться в главное меню\n";
        std::cout << "Введите выбор: ";
        
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }
        
        try {
            switch (choice) {
                case 1: {
                    Point p;
                    std::cout << "Введите координаты вершины (x y): ";
                    std::cin >> p;
                    figure += p;
                    break;
                }
                case 2: {
                    size_t index;
                    std::cout << "Введите индекс вершины: ";
                    std::cin >> index;
                    std::cout << "Вершина " << index << ": " << figure[index] << "\n";
                    break;
                }
                case 3: {
                    Point center;
                    int angle;
                    std::cout << "Введите центральную точку (x y): ";
                    std::cin >> center;
                    std::cout << "Введите угол (градусы, кратно 90): ";
                    std::cin >> angle;
                    figure.rotate(center, angle);
                    std::cout << "Фигура после поворота: " << figure << "\n";
                    break;
                }
                case 0:
                    return;
                default:
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
            clearInputBuffer();
        }
    }
}

int main() {
    while (true) {
        std::cout << "\n=== Главное меню ===\n";
        std::cout << "1. Тестировать операции с точками\n";
        std::cout << "2. Тестировать операции с фигурами\n";
        std::cout << "0. Выход\n";
        std::cout << "Введите выбор: ";
        
        int choice;
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                testPointOperations();
                break;
            case 2:
                testFigureOperations();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}