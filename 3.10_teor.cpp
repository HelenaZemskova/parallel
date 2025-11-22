// Подключение необходимых библиотек
#include <cassert>      // Для макроса assert (проверка условий)
#include <cmath>        // Для математических функций (std::abs)
#include <compare>      // Для трехстороннего сравнения (std::strong_ordering)
#include <istream>      // Для входных потоков (std::istream)
#include <numeric>      // Для математических алгоритмов (std::gcd, std::lcm)
#include <ostream>      // Для выходных потоков (std::ostream)
#include <sstream>      // Для строковых потоков (std::stringstream)
#include <vector>       // Для контейнера std::vector

// Класс Rational - представление рациональных чисел (дробей)
class Rational
{
public:
    // Конструктор по умолчанию и с параметрами
    Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
    {
        reduce();  // Сокращаем дробь при создании
    }

    // Явный оператор приведения к double
    explicit operator double() const
    { 
        return 1.0 * m_num / m_den;  // Вычисляем десятичное представление
    }

    // Оператор сложения с присваиванием
    auto & operator+=(Rational const & other)
    {
        // Находим наименьшее общее кратное знаменателей
        auto lcm = std::lcm(m_den, other.m_den);
        // Приводим числители к общему знаменателю и складываем
        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
        m_den = lcm;  // Обновляем знаменатель
        reduce();     // Сокращаем дробь
        return *this; // Возвращаем ссылку на текущий объект
    }

    // Оператор вычитания с присваиванием (через сложение с отрицательным)
    auto & operator-=(Rational const & other) 
    { 
        return *this += Rational(other.m_num * -1, other.m_den);
    }

    // Оператор умножения с присваиванием
    auto & operator*=(Rational const & other)
    {
        m_num *= other.m_num;  // Умножаем числители
        m_den *= other.m_den;  // Умножаем знаменатели
        reduce();              // Сокращаем дробь
        return *this;          // Возвращаем ссылку на текущий объект
    }
    
    // Оператор деления с присваиванием (через умножение на обратную дробь)
    auto & operator/=(Rational const & other) 
    { 
        return *this *= Rational(other.m_den, other.m_num);
    }

    // Постфиксный оператор инкремента (x++)
    auto const operator++(int) { auto x = *this; *this += 1; return x; }
    // Постфиксный оператор декремента (x--)
    auto const operator--(int) { auto x = *this; *this -= 1; return x; }

    // Префиксный оператор инкремента (++x)
    auto & operator++() { *this += 1; return *this; }
    // Префиксный оператор декремента (--x)
    auto & operator--() { *this -= 1; return *this; }

    // Бинарные арифметические операторы (реализованы через соответствующие операторы с присваиванием)
    friend auto operator+ (Rational lhs, Rational const & rhs) { return lhs += rhs; }
    friend auto operator- (Rational lhs, Rational const & rhs) { return lhs -= rhs; }
    friend auto operator* (Rational lhs, Rational const & rhs) { return lhs *= rhs; }
    friend auto operator/ (Rational lhs, Rational const & rhs) { return lhs /= rhs; }

    // Разделитель для лучшей читаемости кода
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Трехсторонний оператор сравнения (C++20 spaceship operator)
    friend std::strong_ordering operator<=>(Rational const & lhs, Rational const & rhs)
    {
        // Сравниваем a*d и b*c (избегаем деления и преобразуем к общему знаменателю)
        auto left = static_cast<long long>(lhs.m_num) * rhs.m_den;   // a*d
        auto right = static_cast<long long>(rhs.m_num) * lhs.m_den;  // b*c
        
        if (left < right) return std::strong_ordering::less;     // lhs < rhs
        if (left > right) return std::strong_ordering::greater;  // lhs > rhs
        return std::strong_ordering::equal;                      // lhs == rhs
    }

    // Оператор равенства (использует трехстороннее сравнение или собственную проверку)
    friend bool operator==(Rational const & lhs, Rational const & rhs)
    {
        // Предполагаем, что дроби уже приведены к нормальной форме
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

    // Разделитель для лучшей читаемости кода
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Оператор ввода из потока (формат: числитель/знаменатель)
    friend auto & operator>>(std::istream & stream, Rational & rational)
    {
        // Читаем числитель, пропускаем разделитель '/', читаем знаменатель
        return (stream >> rational.m_num).ignore() >> rational.m_den;
    }

    // Оператор вывода в поток (формат: числитель/знаменатель)
    friend auto & operator<<(std::ostream & stream, Rational const & rational)
    {
        return stream << rational.m_num << '/' << rational.m_den;
    }

private:
    // Метод приведения дроби к нормальной форме
    void reduce()
    {
        // Убеждаемся, что знаменатель положительный
        if (m_den < 0)
        {
            m_num = -m_num;  // Меняем знак числителя
            m_den = -m_den;  // Делаем знаменатель положительным
        }

        // Находим наибольший общий делитель числителя и знаменателя
        auto gcd = std::gcd(m_num, m_den);
        // Сокращаем дробь, деля числитель и знаменатель на НОД
        m_num /= gcd;
        m_den /= gcd;
    }

    // Приватные поля: числитель и знаменатель
    int m_num = 0, m_den = 1;
};

// Вспомогательная функция для сравнения вещественных чисел с заданной точностью
auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;  // Сравнение с плавающей точкой через абсолютную погрешность
}

// Главная функция программы
int main()
{
    // Тест 1: Создание объектов
    Rational x = 1, y(2, 1);  // x = 1/1, y = 2/1

    // Демонстрация создания векторов (не связаны с Rational)
    std::vector<int> vector_2(5);              // Вектор из 5 нулей
    std::vector<int> vector_3 = { 1, 2, 3, 4, 5 };  // Вектор с инициализацией

    // Тест 2: Приведение к double
    assert(equal(static_cast<double>(x), 1));  // Проверка явного приведения

    // Тест 3: Операторы с присваиванием
    assert((x += y) == Rational(+3, 1));  // 1 + 2 = 3
    assert((x -= y) == Rational(+1, 1));  // 3 - 2 = 1
    assert((x *= y) == Rational(+2, 1));  // 1 * 2 = 2
    assert((x /= y) == Rational(+1, 1));  // 2 / 2 = 1

    // Тест 4: Инкремент и декремент
    assert((x++) == Rational(+1, 1));  // Постфиксный инкремент (возвращает старое значение)
    assert((x--) == Rational(+2, 1));  // Постфиксный декремент (возвращает старое значение)
    assert((++y) == Rational(+3, 1));  // Префиксный инкремент
    assert((--y) == Rational(+2, 1));  // Префиксный декремент

    [[maybe_unused]] auto z = 0;  // Переменная, которая может быть не использована

    // Тест 5: Бинарные арифметические операторы
    assert((x + y) == Rational(+3, 1));  // 1 + 2 = 3
    assert((x - y) == Rational(-1, 1));  // 1 - 2 = -1
    assert((x * y) == Rational(+2, 1));  // 1 * 2 = 2
    assert((x / y) == Rational(+1, 2));  // 1 / 2 = 1/2

    // Тест 6: Смешанные операции с целыми числами (неявные преобразования)
    assert((x += 1) == Rational(+2, 1));  // 1 + 1 = 2
    assert((x + 1) == Rational(+3, 1));   // 2 + 1 = 3
    assert((1 + y) == Rational(+3, 1));   // 1 + 2 = 3
    assert((1 + 1) == Rational(+2, 1));   // 1 + 1 = 2

    // Разделитель для лучшей читаемости кода
    //////////////////////////////////////////////////////////////////////////////////////////////

    // Тест 7: Трехстороннее сравнение и операторы отношения
    assert((x <=> y) == std::strong_ordering::equal);        // 2 == 2
    assert((x <=> Rational(1, 1)) == std::strong_ordering::greater);  // 2 > 1
    assert((Rational(1, 2) <=> x) == std::strong_ordering::less);     // 0.5 < 2
    
    // Тест 8: Операторы отношения (генерируются автоматически из <=>)
    assert((x < y) == false);   // 2 < 2 = false
    assert((x > y) == false);   // 2 > 2 = false
    assert((x <= y) == true);   // 2 <= 2 = true
    assert((x >= y) == true);   // 2 >= 2 = true
    assert((x == y) == true);   // 2 == 2 = true
    assert((x != y) == false);  // 2 != 2 = false

    // Тест 9: Дополнительные проверки сравнения
    assert(Rational(1, 2) < Rational(2, 3));      // 0.5 < 0.666...
    assert(Rational(3, 4) > Rational(1, 2));      // 0.75 > 0.5
    assert(Rational(2, 4) == Rational(1, 2));     // 2/4 == 1/2 (сокращение работает)
    assert(Rational(1, 3) != Rational(1, 2));     // 1/3 != 1/2

    // Разделитель для лучшей читаемости кода
    //////////////////////////////////////////////////////////////////////////////////////////////

    // Тест 10: Ввод-вывод
    std::stringstream stream_1("1/2");  // Поток с данными для чтения
    std::stringstream stream_2;         // Поток для записи
    
    stream_1 >> x;        // Читаем "1/2" в x
    stream_2 << x;        // Записываем x в stream_2

    assert(stream_2.str() == stream_1.str());  // Проверяем, что записано то же, что прочитано
}