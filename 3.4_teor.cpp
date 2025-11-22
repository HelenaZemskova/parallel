// Подключение необходимых библиотек
#include <iostream>  // Для ввода-вывода (std::cout, std::endl)
#include <cassert>   // Для макроса assert (проверка условий)

// Основной класс, содержащий приватные методы
class Entity {
private:
    // Приватный статический метод version 1
    static void test_v1(int parameter) {
        // Выводим сообщение о доступе к методу и переданное значение
        std::cout << "Access to test_v1 obtained, value = " << parameter << std::endl;
    }
    
    // Приватный статический метод version 2
    static void test_v2() {
        // Выводим сообщение о доступе к методу
        std::cout << "Access to test_v2 obtained" << std::endl;
    }

    // Объявление дружественных классов для контролируемого доступа
    friend class Attorney_v1;  // Дружественный класс для доступа к test_v1
    friend class Attorney_v2;  // Дружественный класс для доступа к test_v2
};

// Класс-посредник для доступа к test_v1 (паттерн Attorney Client)
class Attorney_v1 {
private:
    // Приватный статический метод-обертка для вызова Entity::test_v1
    static void invoke_test_v1(int value) { 
        Entity::test_v1(value);  // Вызов приватного метода класса Entity
    }
    // Объявление дружественного класса, которому разрешен доступ
    friend class Tester_v1;  // Только Tester_v1 может использовать Attorney_v1
};

// Класс-посредник для доступа к test_v2 (паттерн Attorney Client)
class Attorney_v2 {
private:
    // Приватный статический метод-обертка для вызова Entity::test_v2
    static void invoke_test_v2() { 
        Entity::test_v2();  // Вызов приватного метода класса Entity
    }
    // Объявление дружественного класса, которому разрешен доступ
    friend class Tester_v2;  // Только Tester_v2 может использовать Attorney_v2
};

// Класс-тестер для методов version 1
class Tester_v1 {
public:
    // Публичный статический метод для запуска теста
    static void runTest(int testValue) {
        // Вызываем метод-посредник, который имеет доступ к Entity::test_v1
        Attorney_v1::invoke_test_v1(testValue);
    }
};

// Класс-тестер для методов version 2
class Tester_v2 {
public:
    // Публичный статический метод для запуска теста
    static void runTest() {
        // Вызываем метод-посредник, который имеет доступ к Entity::test_v2
        Attorney_v2::invoke_test_v2();
    }
};

// Главная функция программы
int main() {
    // Тестируем доступ к test_v1 через Tester_v1
    Tester_v1::runTest(42);  // Передаем значение 42 для тестирования
    
    // Тестируем доступ к test_v2 через Tester_v2
    Tester_v2::runTest();    // Вызываем без параметров
    
    // Выводим сообщение об успешном выполнении всех тестов
    std::cout << "All tests are passed" << std::endl;
    
    // Возвращаем 0 - признак успешного завершения программы
    return 0;
}