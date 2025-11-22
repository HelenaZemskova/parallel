// Подключение необходимых библиотек
#include <algorithm>   // Для алгоритмов (std::copy, std::swap, std::ranges::copy)
#include <cstddef>     // Для типа std::size_t (беззнаковый тип для размеров)
#include <iostream>    // Для ввода-вывода (std::cout, std::endl)
#include <memory>      // Для умных указателей (не используется напрямую)
#include <utility>     // Для std::exchange (перемещение с обнулением)
#include <cassert>     // Для макроса assert (проверка условий)
#include <cmath>       // Для математических функций (std::pow)

// Класс Vector - собственная реализация динамического массива
class Vector {
private:
    // Приватные поля класса
    int* m_data = nullptr;        // Указатель на массив данных
    std::size_t m_size = 0;       // Текущее количество элементов
    std::size_t m_capacity = 0;   // Текущая емкость (размер выделенной памяти)

public:
    // Конструктор по умолчанию - создает пустой вектор
    Vector() = default;  // Компилятор генерирует реализацию
    
    // Конструктор с заданной начальной емкостью
    Vector(std::size_t initial_capacity) : m_capacity(initial_capacity) {
        // Если емкость больше 0, выделяем память
        if (m_capacity > 0) {
            m_data = new int[m_capacity];  // Выделение массива в куче
        }
    }
    
    // Конструктор из списка инициализации {1, 2, 3, 4}
    Vector(std::initializer_list<int> list) : m_size(list.size()), m_capacity(list.size()) {
        // Если список не пустой, копируем элементы
        if (m_capacity > 0) {
            m_data = new int[m_capacity];  // Выделение памяти
            std::copy(list.begin(), list.end(), m_data);  // Копирование элементов
        }
    }
    
    // Конструктор копирования (глубокое копирование)
    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        // Если исходный вектор не пустой, копируем его данные
        if (m_capacity > 0) {
            m_data = new int[m_capacity];  // Выделение новой памяти
            std::copy(other.m_data, other.m_data + other.m_size, m_data);  // Копирование данных
        }
    }
    
    // Конструктор перемещения (перехват ресурсов)
    Vector(Vector&& other) noexcept  // noexcept - гарантия отсутствия исключений
        : m_data(std::exchange(other.m_data, nullptr)),      // Забираем указатель, обнуляем у other
          m_size(std::exchange(other.m_size, 0)),           // Забираем размер, обнуляем у other
          m_capacity(std::exchange(other.m_capacity, 0)) {} // Забираем емкость, обнуляем у other
    
    // Оператор присваивания (copy-and-swap идиома)
    Vector& operator=(Vector other) {  // Параметр передается по значению (копирование/перемещение)
        swap(other);  // Обмен содержимым с временным объектом
        return *this; // Возвращаем ссылку на текущий объект
    }
    
    // Деструктор - освобождает выделенную память
    ~Vector() {
        delete[] m_data;  // Освобождение массива, выделенного через new[]
    }
    
    // Метод обмена содержимым двух векторов
    void swap(Vector& other) noexcept {  // noexcept - гарантия отсутствия исключений
        std::swap(m_data, other.m_data);        // Обмен указателями
        std::swap(m_size, other.m_size);        // Обмен размерами
        std::swap(m_capacity, other.m_capacity);// Обмен емкостями
    }
    
    // Разделитель для лучшей читаемости кода
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // Методы доступа к состоянию вектора
    std::size_t size() const { return m_size; }           // Текущий размер
    std::size_t capacity() const { return m_capacity; }   // Текущая емкость
    bool empty() const { return m_size == 0; }           // Проверка на пустоту
    
    // Оператор доступа к элементу по индексу (неконстантная версия)
    int& operator[](std::size_t index) { return m_data[index]; }
    // Оператор доступа к элементу по индексу (константная версия)
    const int& operator[](std::size_t index) const { return m_data[index]; }
    
    // Метод резервирования памяти (увеличение емкости)
    void reserve(std::size_t new_capacity) {
        // Если новая емкость не больше текущей, ничего не делаем
        if (new_capacity <= m_capacity)
            return;

        // Выделяем новый массив большего размера
        int *new_array = new int[new_capacity];

        // Если в старом массиве были данные, копируем их
        if (m_data) {
            std::ranges::copy(m_data, m_data + m_size, new_array);  // Копирование данных
            delete[] m_data;  // Освобождаем старую память
        }

        // Обновляем указатель и емкость
        m_data = new_array;
        m_capacity = new_capacity;
    }
    
    // Метод добавления элемента в конец вектора
    void push_back(int value) {
        // Если массив заполнен, увеличиваем емкость
        if (m_size == m_capacity) {
            // Стратегия роста: если емкость 0, резервируем 1, иначе удваиваем
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        // Добавляем элемент в конец
        m_data[m_size] = value;
        ++m_size;  // Увеличиваем счетчик элементов
    }
    
    // Метод очистки вектора (не освобождает память)
    void clear() {
        m_size = 0;  // Просто обнуляем размер - данные остаются в памяти
    }
    
    // Разделитель для лучшей читаемости кода
    ////////////////////////////////////////////////////////////////////////////////////////////////////
};

// Главная функция программы
int main() {
    // Тест 1: Создание пустого вектора
    Vector vec;  // Создаем вектор с помощью конструктора по умолчанию
    assert(vec.empty());  // Проверяем, что вектор пустой
    std::cout << "empty test passed \n";  // Сообщение об успешном тесте
    
    // Тест 2: Добавление элементов и проверка роста емкости
    for (int i = 1; i <= 20; ++i) {
        vec.push_back(i);          // Добавляем элемент i в конец вектора
        assert(vec[i-1] == i);     // Проверяем, что элемент добавлен корректно
        assert(vec.size() == i);   // Проверяем, что размер увеличился
        std::cout << vec.capacity() << std::endl;  // Выводим текущую емкость для наблюдения
        // Закомментированная проверка на геометрический рост емкости
        //assert(vec.capacity() == std::pow(2, i / 2));
    }
    std::cout << "push back and capacity growth test passed \n";  // Сообщение об успехе
    
    // Тест 3: Очистка вектора
    vec.clear();  // Очищаем вектор
    assert(vec.size() == 0);        // Проверяем, что размер стал 0
    assert(vec.capacity() == 32);   // Проверяем, что емкость сохранилась (после 20 элементов)
    std::cout << "vector.clear test passed \n";  // Сообщение об успехе
    
    return 0;  // Успешное завершение программы
}