// Подключение необходимых библиотек
#include <vector>    // Для использования std::vector (динамический массив)
#include <iostream>  // Для ввода-вывода (std::cout, std::endl)
#include <cassert>   // Для макроса assert (проверка условий)
#include <algorithm> // Для алгоритмов std::max и std::min

// Структура для представления прямоугольника
struct Rectangle {
    // Координаты верхнего левого угла
    int topLeftX, topLeftY;
    // Координаты нижнего правого угла  
    int bottomRightX, bottomRightY;

    // Конструктор для инициализации прямоугольника
    Rectangle(int x1, int y1, int x2, int y2) 
        : topLeftX(x1), topLeftY(y1), bottomRightX(x2), bottomRightY(y2) {}
};

// Функция вычисления площади пересечения нескольких прямоугольников
int calculateIntersectionArea(const std::vector<Rectangle>& rectangles) {
    // Если список прямоугольников пуст, возвращаем -1 (ошибка)
    if (rectangles.empty()) return -1;
    
    // Инициализируем область пересечения первым прямоугольником
    int intersectionLeftX = rectangles[0].topLeftX;      // Левая граница
    int intersectionTopY = rectangles[0].topLeftY;       // Верхняя граница
    int intersectionRightX = rectangles[0].bottomRightX; // Правая граница
    int intersectionBottomY = rectangles[0].bottomRightY;// Нижняя граница
    
    // Проходим по всем оставшимся прямоугольникам
    for (size_t index = 1; index < rectangles.size(); ++index) {
        // Обновляем левую границу - берем максимальную из текущих левых границ
        intersectionLeftX = std::max(intersectionLeftX, rectangles[index].topLeftX);
        // Обновляем верхнюю границу - берем максимальную из текущих верхних границ
        intersectionTopY = std::max(intersectionTopY, rectangles[index].topLeftY);
        // Обновляем правую границу - берем минимальную из текущих правых границ
        intersectionRightX = std::min(intersectionRightX, rectangles[index].bottomRightX);
        // Обновляем нижнюю границу - берем минимальную из текущих нижних границ
        intersectionBottomY = std::min(intersectionBottomY, rectangles[index].bottomRightY);
    }
    
    // Проверяем, существует ли пересечение
    // Если левая граница правее правой или верхняя граница ниже нижней - пересечения нет
    if (intersectionLeftX > intersectionRightX || intersectionTopY > intersectionBottomY) {
        return -1; // Прямоугольники не пересекаются
    }
    
    // Проверяем вырожденный случай (пересечение по линии или точке)
    if (intersectionLeftX == intersectionRightX || intersectionTopY == intersectionBottomY) {
        return 0; // Площадь пересечения равна 0 (касание по границе)
    }

    // Вычисляем ширину и высоту области пересечения
    int width = intersectionRightX - intersectionLeftX;   // Ширина пересечения
    int height = intersectionBottomY - intersectionTopY;  // Высота пересечения
    // Возвращаем площадь пересечения (ширина × высота)
    return width * height;
}

// Функция вычисления ограничивающего прямоугольника (bounding box)
Rectangle computeBoundingBox(const std::vector<Rectangle>& rectangles) {
    // Если список пуст, возвращаем нулевой прямоугольник
    if (rectangles.empty()) {
        return Rectangle(0, 0, 0, 0);
    }
    
    // Инициализируем границы первым прямоугольником
    int minX = rectangles[0].topLeftX;      // Минимальная X координата
    int minY = rectangles[0].topLeftY;      // Минимальная Y координата
    int maxX = rectangles[0].bottomRightX;  // Максимальная X координата
    int maxY = rectangles[0].bottomRightY;  // Максимальная Y координата
    
    // Проходим по всем прямоугольникам для нахождения общих границ
    for (size_t idx = 1; idx < rectangles.size(); ++idx) {
        // Обновляем минимальную X координату
        minX = std::min(minX, rectangles[idx].topLeftX);
        // Обновляем минимальную Y координату
        minY = std::min(minY, rectangles[idx].topLeftY);
        // Обновляем максимальную X координату
        maxX = std::max(maxX, rectangles[idx].bottomRightX);
        // Обновляем максимальную Y координату
        maxY = std::max(maxY, rectangles[idx].bottomRightY);
    }
    
    // Возвращаем ограничивающий прямоугольник
    return Rectangle(minX, minY, maxX, maxY);
}

// Главная функция программы
int main() {
    // Тест 1: Пересекающиеся прямоугольники
    std::vector<Rectangle> testCase1 = {
        Rectangle(0, 0, 10, 10),   // Первый прямоугольник
        Rectangle(5, 5, 15, 15)    // Второй прямоугольник (пересекается с первым)
    };
    // Проверяем, что площадь пересечения равна 25
    assert(calculateIntersectionArea(testCase1) == 25);
    
    // Тест 2: Непересекающиеся прямоугольники
    std::vector<Rectangle> testCase2 = {
        Rectangle(0, 0, 10, 10),   // Первый прямоугольник
        Rectangle(25, 15, 45, 55)  // Второй прямоугольник (далеко от первого)
    };
    // Проверяем, что пересечения нет (возвращается -1)
    assert(calculateIntersectionArea(testCase2) == -1);
    
    // Тест 3: Вырожденное пересечение (касание по границе)
    std::vector<Rectangle> testCase3 = {
        Rectangle(0, 0, 10, 10),   // Первый прямоугольник
        Rectangle(5, 10, 45, 55)   // Второй прямоугольник (касается сверху)
    };
    // Проверяем, что площадь пересечения равна 0
    assert(calculateIntersectionArea(testCase3) == 0);
    
    // Тест 4: Проверка ограничивающего прямоугольника
    Rectangle boundingRect = computeBoundingBox(testCase1);
    // Проверяем координаты ограничивающего прямоугольника
    assert(boundingRect.topLeftX == 0 && boundingRect.topLeftY == 0);
    assert(boundingRect.bottomRightX == 15 && boundingRect.bottomRightY == 15);
    
    // Если все тесты прошли, выводим сообщение об успехе
    std::cout << "All tests passed" << std::endl;
    
    // Возвращаем 0 - признак успешного завершения программы
    return 0;
}