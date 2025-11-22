// Подключение необходимых библиотек
#include <iostream>     // Для ввода-вывода (std::cout, std::endl)
#include <numbers>      // Для математических констант (std::numbers::pi)
#include <cmath>        // Для математических функций (std::sqrt, std::abs)
#include <cassert>      // Для макроса assert (проверка условий)

// Класс для представления треугольника
class Triangle {
private:
    // Приватные поля: длины трех сторон треугольника
    double side1, side2, side3;

public:
    // Конструктор класса Triangle - инициализирует стороны треугольника
    Triangle(double first, double second, double third) 
        : side1(first), side2(second), side3(third) {} // Список инициализации

    // Метод вычисления площади треугольника по формуле Герона
    double area() const {
        // Вычисляем полупериметр (половина периметра)
        double semiPerimeter = perimeter() / 2.0;
        // Вычисляем произведение по формуле Герона: p(p-a)(p-b)(p-c)
        double product = semiPerimeter * (semiPerimeter - side1) * 
                        (semiPerimeter - side2) * (semiPerimeter - side3);
        // Возвращаем квадратный корень из произведения - площадь треугольника
        return std::sqrt(product);
    }

    // Метод вычисления периметра треугольника
    double perimeter() const {
        // Периметр = сумма длин всех сторон
        return side1 + side2 + side3;
    }
};

// Класс для представления квадрата
class Square {
private:
    // Приватное поле: длина стороны квадрата
    double sideLength;

public:
    // Конструктор класса Square - инициализирует длину стороны
    Square(double length) : sideLength(length) {}

    // Метод вычисления площади квадрата
    double area() const {
        // Площадь квадрата = сторона × сторона
        return sideLength * sideLength;
    }

    // Метод вычисления периметра квадрата
    double perimeter() const {
        // Периметр квадрата = 4 × сторона
        return 4.0 * sideLength;
    }
};

// Класс для представления окружности
class Circle {
private:
    // Приватное поле: радиус окружности
    double circleRadius;
    
public:
    // Конструктор класса Circle - инициализирует радиус
    Circle(double r) : circleRadius(r) {}
    
    // Метод вычисления площади круга
    double area() const {
        // Площадь круга = π × радиус²
        return std::numbers::pi * circleRadius * circleRadius;
    }
    
    // Метод вычисления длины окружности (периметра)
    double perimeter() const {
        // Длина окружности = 2 × π × радиус
        return 2.0 * std::numbers::pi * circleRadius;
    }
};

// Главная функция программы
int main() {
    // Тестирование класса Triangle
    // Создаем треугольник со сторонами 3, 4, 5 (египетский треугольник)
    Triangle triangle(3.0, 4.0, 5.0);
    // Проверяем периметр: 3 + 4 + 5 = 12
    assert(triangle.perimeter() == 12.0);
    // Проверяем площадь: для треугольника 3-4-5 площадь = 6
    assert(triangle.area() == 6.0);
    // Выводим сообщение об успешном тесте
    std::cout << "Triangle test is passed" << std::endl;

    // Тестирование класса Square
    // Создаем квадрат со стороной 5
    Square square(5.0);
    // Проверяем периметр: 4 × 5 = 20
    assert(square.perimeter() == 20.0);
    // Проверяем площадь: 5 × 5 = 25
    assert(square.area() == 25.0);
    // Выводим сообщение об успешном тесте
    std::cout << "Square test is passed" << std::endl;

    // Тестирование класса Circle
    // Создаем окружность с радиусом 3
    Circle circle(3.0);
    // Проверяем длину окружности: 2 × π × 3 ≈ 18.8496
    // Используем сравнение с погрешностью для вещественных чисел
    assert(std::abs(circle.perimeter() - 18.8496) <= 1e-3);
    // Проверяем площадь круга: π × 3² ≈ 28.2743
    // Используем сравнение с погрешностью для вещественных чисел
    assert(std::abs(circle.area() - 28.2743) <= 1e-3);
    // Выводим сообщение об успешном тесте
    std::cout << "Circle test is passed" << std::endl;

    // Возвращаем 0 - признак успешного завершения программы
    return 0;
}