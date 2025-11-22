// Подключение необходимых библиотек
#include <iostream>  // Для ввода-вывода (std::cout, std::endl)
#include <cassert>   // Для макроса assert (проверка условий)

// Класс односвязного списка
class List {
private:
    // Внутренняя структура узла списка
    struct Node {
        int value;    // Значение, хранящееся в узле
        Node* next;   // Указатель на следующий узел
        
        // Конструктор узла
        Node(int val) : value(val), next(nullptr) {} // Инициализация значения и нулевого указателя
    };
    
    // Указатели на начало и конец списка
    Node* headPtr;  // Указатель на первый узел
    Node* tailPtr;  // Указатель на последний узел

public:
    // Конструктор по умолчанию
    List() : headPtr(nullptr), tailPtr(nullptr) {} // Инициализация пустого списка
    
    // Метод проверки пустоты списка
    bool empty() const {
        return headPtr == nullptr; // Если headPtr равен nullptr, список пуст
    }
    
    // Метод вывода всех элементов списка
    void show() const {
        Node* iterator = headPtr; // Создаем итератор, начинающий с головы
        // Проходим по всем узлам до конца списка
        while (iterator != nullptr) {
            std::cout << iterator->value << " "; // Выводим значение текущего узла
            iterator = iterator->next; // Переходим к следующему узлу
        }
        std::cout << std::endl; // Переход на новую строку после вывода
    }

    // Метод добавления элемента в начало списка
    void push_front(int value) {
        Node* newElement = new Node(value); // Создаем новый узел
        if (!empty()) { // Если список не пуст
            newElement->next = headPtr; // Новый узел указывает на старую голову
            headPtr = newElement; // Голова теперь указывает на новый узел
        } else { // Если список пуст
            headPtr = newElement; // Голова указывает на новый узел
            tailPtr = newElement; // Хвост также указывает на новый узел
        }
    }

    // Метод добавления элемента в конец списка
    void push_back(int value) {
        Node* newElement = new Node(value); // Создаем новый узел
        if (!empty()) { // Если список не пуст
            tailPtr->next = newElement; // Старый хвост указывает на новый узел
            tailPtr = newElement; // Хвост теперь указывает на новый узел
        } else { // Если список пуст
            headPtr = newElement; // Голова указывает на новый узел
            tailPtr = newElement; // Хвост также указывает на новый узел
        }
    }

    // Метод удаления элемента из начала списка
    void pop_front() {
        if (empty()) return; // Если список пуст, ничего не делаем
        Node* nextElement = headPtr->next; // Сохраняем указатель на следующий узел
        delete headPtr; // Освобождаем память текущей головы
        headPtr = nextElement; // Голова теперь указывает на следующий узел
        if (headPtr == nullptr) { // Если список стал пустым
            tailPtr = nullptr; // Хвост также должен быть nullptr
        }
    }

    // Метод удаления элемента из конца списка
    void pop_back() {
        if (empty()) return; // Если список пуст, ничего не делаем
        if (tailPtr == headPtr) { // Если в списке только один элемент
            delete headPtr; // Освобождаем память
            tailPtr = nullptr; // Обнуляем хвост
            headPtr = nullptr; // Обнуляем голову
            return; // Выходим из метода
        }
        // Ищем предпоследний узел
        Node* iterator = headPtr; // Начинаем с головы
        while (iterator->next != tailPtr) { // Пока не дойдем до предпоследнего
            iterator = iterator->next; // Переходим к следующему узлу
        }
        delete tailPtr; // Освобождаем память последнего узла
        tailPtr = iterator; // Хвост теперь указывает на предпоследний узел
        iterator->next = nullptr; // Новый конец списка указывает на nullptr
    }

    // Метод получения среднего элемента (медианы) списка
    int get() const {
        if (empty()) return -1; // Если список пуст, возвращаем -1
        Node* fastPtr = headPtr; // Быстрый указатель (двигается на 2 шага)
        Node* slowPtr = headPtr; // Медленный указатель (двигается на 1 шаг)
        bool moveSlow = false;   // Флаг для перемещения медленного указателя
        // Проходим по списку быстрым указателем
        while (fastPtr->next != nullptr) {
            if (moveSlow) {
                slowPtr = slowPtr->next; // Перемещаем медленный указатель
            }
            moveSlow = !moveSlow; // Инвертируем флаг (чередуем шаги)
            fastPtr = fastPtr->next; // Всегда перемещаем быстрый указатель
        }
        return slowPtr->value; // Возвращаем значение среднего элемента
    }
    
    // Деструктор - освобождает всю память
    ~List() {
        // Последовательно удаляем все элементы с начала
        while (!empty()) {
            pop_front(); // Удаляем первый элемент
        }
    }
};

// Главная функция программы
int main() {
    List testList; // Создаем тестовый список
    assert(testList.empty()); // Проверяем, что список пуст
    testList.push_back(1); // Добавляем элемент в конец
    assert(!testList.empty()); // Проверяем, что список не пуст
    std::cout << "empty() test is passed" << std::endl; // Сообщение об успехе
    testList.pop_back(); // Удаляем элемент из конца
    
    // Тестирование push_back
    testList.push_back(1); // Добавляем 1 в конец
    testList.push_back(2); // Добавляем 2 в конец
    testList.push_back(3); // Добавляем 3 в конец
    std::cout << "After push_back: ";
    testList.show(); // Выводим список: 1 2 3
    
    // Тестирование push_front
    testList.push_front(0); // Добавляем 0 в начало
    std::cout << "After push_front: ";
    testList.show(); // Выводим список: 0 1 2 3
    assert(testList.get() == 1); // Проверяем средний элемент для 4 элементов
    std::cout << "The middle element for size 5 is correct" << std::endl;
    
    // Тестирование pop_front
    testList.pop_front(); // Удаляем первый элемент
    std::cout << "After pop_front: ";
    testList.show(); // Выводим список: 1 2 3
    assert(testList.get() == 2); // Проверяем средний элемент для 3 элементов
    std::cout << "The middle element for size 3 is correct" << std::endl;
    
    // Тестирование pop_back
    testList.pop_back(); // Удаляем последний элемент
    std::cout << "After pop_back: ";
    testList.show(); // Выводим список: 1 2
    assert(testList.get() == 1); // Проверяем средний элемент для 2 элементов
    std::cout << "The middle element for size 2 is correct" << std::endl;

    return 0; // Успешное завершение программы
}