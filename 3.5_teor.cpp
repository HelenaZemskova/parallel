// Подключение необходимых библиотек
#include <iostream>  // Для ввода-вывода (std::cout, std::endl)
#include <string>    // Для работы со строками (std::string)

// Базовый класс версии 1
class Entity_v1 {
public:
    // Виртуальный метод test - может быть переопределен в производных классах
    virtual void test(const std::string& msg) {
        // Вывод сообщения с идентификатором класса
        std::cout << "Entity_v1::test: " << msg << std::endl;
    }
    
    // Виртуальный деструктор для корректного удаления производных классов
    virtual ~Entity_v1() = default;  // = default - компилятор генерирует реализацию
};

// Базовый класс версии 2
class Entity_v2 {
public:
    // Виртуальный метод test - может быть переопределен в производных классах
    virtual void test(const std::string& msg) {
        // Вывод сообщения с идентификатором класса
        std::cout << "Entity_v2::test: " << msg << std::endl;
    }
    
    // Виртуальный деструктор для корректного удаления производных классов
    virtual ~Entity_v2() = default;  // = default - компилятор генерирует реализацию
};

// Адаптер для Entity_v1 - паттерн Adapter для изменения интерфейса
class Adapter_v1 : public Entity_v1 {
public:
    // Чисто виртуальный метод - делает класс абстрактным
    // Клиенты должны реализовать этот метод вместо прямого переопределения test()
    virtual void test_v1(const std::string& msg) = 0;
    
private:
    // Приватное финальное переопределение базового метода test
    // Ключевое слово final запрещает дальнейшее переопределение в производных классах
    void test(const std::string& msg) override final {
        // Делегируем вызов новому интерфейсу test_v1
        test_v1(msg);
    }
};

// Адаптер для Entity_v2 - паттерн Adapter для изменения интерфейса
class Adapter_v2 : public Entity_v2 {
public:
    // Чисто виртуальный метод - делает класс абстрактным
    // Клиенты должны реализовать этот метод вместо прямого переопределения test()
    virtual void test_v2(const std::string& msg) = 0;
    
private:
    // Приватное финальное переопределение базового метода test
    // Ключевое слово final запрещает дальнейшее переопределение в производных классах
    void test(const std::string& msg) override final {
        // Делегируем вызов новому интерфейсу test_v2
        test_v2(msg);
    }
};

// Клиентский класс, который использует оба адаптера (множественное наследование)
class Client : public Adapter_v1, public Adapter_v2 {
public:
    // Реализация интерфейса Adapter_v1
    void test_v1(const std::string& msg) override {
        // Вывод сообщения с идентификатором метода и класса
        std::cout << "Client::test_v1: " << msg << std::endl;
    }
    
    // Реализация интерфейса Adapter_v2
    void test_v2(const std::string& msg) override {
        // Вывод сообщения с идентификатором метода и класса
        std::cout << "Client::test_v2: " << msg << std::endl;
    }
};

// Главная функция программы
int main() {
    // Создаем объект клиентского класса
    Client client;
    
    // Создаем указатель на Entity_v1, который указывает на клиентский объект
    Entity_v1* ptr1 = &client;
    // Вызываем метод test() через интерфейс Entity_v1
    // Благодаря виртуальным функциям вызывается Client::test_v1
    ptr1->test("Message from Entity_v1");
    
    // Создаем указатель на Entity_v2, который указывает на клиентский объект
    Entity_v2* ptr2 = &client;
    // Вызываем метод test() через интерфейс Entity_v2
    // Благодаря виртуальным функциям вызывается Client::test_v2
    ptr2->test("Message from Entity_v2");
    
    // Возвращаем 0 - признак успешного завершения программы
    return 0;
}