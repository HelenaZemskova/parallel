// Подключение необходимых библиотек
#include <iostream>   // Для ввода-вывода (std::cout, std::endl)
#include <numbers>    // Для математических констант (std::numbers::pi)
#include <cmath>      // Для математических функций (std::sqrt, std::abs)
#include <cassert>    // Для макроса assert (проверка условий)
#include <vector>     // Для контейнера std::vector

// Абстрактный базовый класс для всех фигур
class Shape {
public:
    // Виртуальный деструктор для корректного удаления производных классов
    virtual ~Shape() = default;  // = default - компилятор генерирует реализацию
    
    // Чисто виртуальная функция для вычисления периметра (делает класс абстрактным)
    virtual double perimeter() const = 0;
    
    // Чисто виртуальная функция для вычисления площади (делает класс абстрактным)
    virtual double area() const = 0;
};

// Класс треугольника, наследуется от Shape
class Triangle : public Shape {
private:
    // Приватные поля: длины трех сторон треугольника
    double side1, side2, side3;

public:
    // Конструктор треугольника - инициализирует длины сторон
    Triangle(double first, double second, double third) 
        : side1(first), side2(second), side3(third) {}  // Список инициализации

    // Метод вычисления площади треугольника по формуле Герона
    double area() const override final {  // override final - переопределение, запрет дальнейшего переопределения
        // Вычисляем полупериметр
        double semiPerimeter = perimeter() / 2.0;
        // Вычисляем произведение по формуле Герона: p(p-a)(p-b)(p-c)
        double product = semiPerimeter * (semiPerimeter - side1) * 
                        (semiPerimeter - side2) * (semiPerimeter - side3);
        // Возвращаем квадратный корень из произведения - площадь треугольника
        return std::sqrt(product);
    }

    // Метод вычисления периметра треугольника
    double perimeter() const override final {  // override final - переопределение, запрет дальнейшего переопределения
        // Периметр = сумма длин всех сторон
        return side1 + side2 + side3;
    }
};

// Класс квадрата, наследуется от Shape, final - запрет дальнейшего наследования
class Square final : public Shape {
private:
    // Приватное поле: длина стороны квадрата
    double sideLength;

public:
    // Конструктор квадрата - инициализирует длину стороны
    Square(double length) : sideLength(length) {}

    // Метод вычисления площади квадрата
    double area() const override {  // override - явное указание переопределения
        // Площадь квадрата = сторона × сторона
        return sideLength * sideLength;
    }

    // Метод вычисления периметра квадрата
    double perimeter() const override {  // override - явное указание переопределения
        // Периметр квадрата = 4 × сторона
        return 4.0 * sideLength;
    }
};

// Класс окружности, наследуется от Shape, final - запрет дальнейшего наследования
class Circle final : public Shape {
private:
    // Приватное поле: радиус окружности
    double circleRadius;
    
public:
    // Конструктор окружности - инициализирует радиус
    Circle(double r) : circleRadius(r) {}
    
    // Метод вычисления площади круга
    double area() const override {  // override - явное указание переопределения
        // Площадь круга = π × радиус²
        return std::numbers::pi * circleRadius * circleRadius;
    }
    
    // Метод вычисления длины окружности (периметра)
    double perimeter() const override {  // override - явное указание переопределения
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
    std::cout << "Triangle test passed" << std::endl;

    // Тестирование класса Square
    // Создаем квадрат со стороной 5
    Square square(5.0);
    // Проверяем периметр: 4 × 5 = 20
    assert(square.perimeter() == 20.0);
    // Проверяем площадь: 5 × 5 = 25
    assert(square.area() == 25.0);
    // Выводим сообщение об успешном тесте
    std::cout << "Square test passed" << std::endl;

    // Тестирование класса Circle
    // Создаем окружность с радиусом 3
    Circle circle(3.0);
    // Проверяем длину окружности: 2 × π × 3 ≈ 18.8496 (с погрешностью 0.001)
    assert(std::abs(circle.perimeter() - 18.8496) <= 1e-3);
    // Проверяем площадь круга: π × 3² ≈ 28.2743 (с погрешностью 0.001)
    assert(std::abs(circle.area() - 28.2743) <= 1e-3);
    // Выводим сообщение об успешном тесте
    std::cout << "Circle test passed" << std::endl;
    
    // Демонстрация полиморфизма через вектор указателей на базовый класс
    std::vector<Shape*> shapes;  // Вектор указателей на базовый класс Shape
    
    // Добавляем в вектор объекты разных типов (полиморфизм)
    shapes.push_back(new Triangle(3.0, 4.0, 5.0));  // Создаем треугольник в куче
    shapes.push_back(new Square(5.0));               // Создаем квадрат в куче
    shapes.push_back(new Circle(3.0));               // Создаем окружность в куче
    
    // Демонстрация работы с фигурами через базовый интерфейс
    std::cout << "Testing through std::vector<Shape*>:" << std::endl;
    // Проходим по всем фигурам в векторе
    for (size_t i = 0; i < shapes.size(); ++i) {
        // Вызываем виртуальные методы - работает полиморфизм
        std::cout << "Figure " << i + 1 << ": perimeter = " 
                  << shapes[i]->perimeter() << ", area = " 
                  << shapes[i]->area() << std::endl;
    }
    
    // Освобождаем память, выделенную через new
    for (size_t i = 0; i < shapes.size(); ++i) {
        delete shapes[i];  // Удаляем объект, вызывается соответствующий деструктор
    }
    shapes.clear();  // Очищаем вектор (удаляем все указатели)
    
    // Финальное сообщение об успешном выполнении всех тестов
    std::cout << "All tests are passed successfully" << std::endl;
    
    // Возвращаем 0 - признак успешного завершения программы
    return 0;
}