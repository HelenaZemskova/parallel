// Подключение стандартных библиотек C++
#include <iostream>      // Для ввода-вывода (std::cout, std::endl)
#include <numeric>       // Для математических функций (std::gcd, std::lcm)
#include <cstdlib>       // Для функции std::abs (модуль числа)
#include <random>        // Для генерации случайных чисел
#include <chrono>        // Для работы со временем (измерение производительности)
#include <cassert>       // Для макроса assert (проверка условий)

// Рекурсивная функция вычисления наибольшего общего делителя (НОД)
int findGCDRecursive(int first, int second) {
    // Базовый случай рекурсии: если второе число равно 0
    if (second == 0) 
        // Возвращаем модуль первого числа (НОД всегда неотрицателен)
        return std::abs(first);
    // Рекурсивный вызов: НОД(a, b) = НОД(b, a mod b)
    return findGCDRecursive(second, first % second);
}

// Итеративная функция вычисления наибольшего общего делителя (НОД)
int findGCDIterative(int first, int second) {
    // Приводим числа к неотрицательным значениям
    first = std::abs(first);
    second = std::abs(second);
    // Алгоритм Евклида в цикле
    while (second != 0) {
        // Сохраняем текущее значение второго числа
        int remainder = second;
        // Вычисляем остаток от деления first на second
        second = first % second;
        // Присваиваем first предыдущее значение second
        first = remainder;
    }
    // Когда second стал 0, first содержит НОД
    return first;
}

// Функция вычисления наименьшего общего кратного (НОК)
int findLCM(int first, int second) {
    // Если любое из чисел равно 0, НОК равен 0
    if (first == 0 || second == 0) 
        return 0;
    // Вычисляем НОД с помощью итеративной функции
    int gcd_result = findGCDIterative(first, second);
    // Формула: НОК(a, b) = |a * b| / НОД(a, b)
    return std::abs(first * second) / gcd_result;
}

// Главная функция программы
int main() {
    // Получаем текущее время для инициализации генератора случайных чисел
    auto time_point = std::chrono::steady_clock::now();
    // Преобразуем время в числовое значение (seed)
    unsigned seed_value = time_point.time_since_epoch().count();
    // Создаем генератор случайных чисел Mersenne Twister с полученным seed
    std::mt19937 random_generator(seed_value);
    // Создаем распределение для целых чисел от 1 до 1000
    std::uniform_int_distribution<int> number_range(1, 1000);
    
    // Генерируем два случайных числа
    int num1 = number_range(random_generator);
    int num2 = number_range(random_generator);
    
    // Выводим сгенерированные числа для отладки
    std::cout << "Test values: " << num1 << " & " << num2 << std::endl;
    
    // Вычисляем НОД тремя способами:
    // 1. Рекурсивная реализация
    int gcd_recursive_result = findGCDRecursive(num1, num2);
    // 2. Итеративная реализация  
    int gcd_iterative_result = findGCDIterative(num1, num2);
    // 3. Стандартная функция из библиотеки
    int gcd_standard = std::gcd(num1, num2);
    
    // Вычисляем НОК двумя способами:
    // 1. Кастомная реализация
    int lcm_custom = findLCM(num1, num2);
    // 2. Стандартная функция из библиотеки
    int lcm_standard = std::lcm(num1, num2);
    
    // Проверяем корректность реализаций:
    // Все три метода вычисления НОД должны давать одинаковый результат
    assert(gcd_recursive_result == gcd_standard);
    // Итеративная и стандартная реализации НОД должны совпадать
    assert(gcd_iterative_result == gcd_standard);
    // Кастомная и стандартная реализации НОК должны совпадать
    assert(lcm_custom == lcm_standard);
    
    // Выводим результаты вычислений
    std::cout << "Calculation results:" << std::endl;
    // Выводим НОД (можно использовать любой из результатов, они одинаковы)
    std::cout << "GCD = " << gcd_recursive_result << std::endl;
    // Выводим НОК
    std::cout << "LCM = " << lcm_custom << std::endl;
    
    // Возвращаем 0 - признак успешного завершения программы
    return 0;
}