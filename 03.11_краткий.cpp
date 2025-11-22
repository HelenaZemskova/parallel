// ПУБЛИЧНОЕ НАСЛЕДОВАНИЕ (PUBLIC INHERITANCE) В C++
// Демонстрирует: базовый и производный классы, уровни доступа, name hiding

#include <print>

// БАЗОВЫЙ КЛАСС Entity
// Уровни доступа:
// - public: доступен везде
// - protected: доступен внутри класса и в наследниках
// - private: доступен только внутри класса
class Entity
{
public :
	// Конструктор с параметром x
	// Список инициализации : m_x(x) более эффективен, чем присваивание в теле
	Entity(int x) : m_x(x)
	{
		std::print("Entity::Entity\n");
	}

	// Публичный константный метод (const означает, что метод не изменяет объект)
	void test_v1() const { std::print("Entity::test_v1\n"); }

	// Будет переопределен в производном классе (name hiding, НЕ virtual)
	void test_v2() const { std::print("Entity::test_v2\n"); }

protected :
	// Защищенный метод - доступен в наследниках, но не извне
    void test_v3() const 
	{ 
		std::print("Entity::test_v3\n"); 
	}

private :
	// Приватное поле - недоступно в наследниках
	int m_x = 0;  // Инициализация в объявлении (C++11)
};

// ПРОИЗВОДНЫЙ КЛАСС Client
// public Entity - публичное наследование: сохраняется уровень доступа
// Семантика: "Client ЯВЛЯЕТСЯ Entity" (IS-A relationship)
class Client : public Entity
{
public :
	// Конструктор производного класса
	// ПОРЯДОК ВЫПОЛНЕНИЯ:
	// 1. Конструктор базового класса Entity(x)
	// 2. Инициализация полей производного класса m_y(y)
	// 3. Тело конструктора Client
	Client(int x, int y) : Entity(x), m_y(y)
	{
		std::print("Client::Client\n");
	}

	// ПЕРЕОПРЕДЕЛЕНИЕ метода test_v2 (name hiding)
	// Без virtual - это НЕ полиморфизм! Статическое связывание на этапе компиляции
	void test_v2() const
	{
		std::print("Client::test_v2\n");

		// test_v2(); // ОШИБКА! Рекурсивный вызов

		// Явный вызов метода базового класса через оператор ::
		Entity::test_v2();
	}

	// Директива using изменяет уровень доступа: protected -> public
	// Теперь client.test_v3() доступен извне
	using Entity::test_v3;

private :
	int m_y = 0;
};

int main()
{
	// Создание объекта базового класса
    Entity entity(1);

	// static_assert - проверка во время компиляции (без накладных расходов)
	// Entity содержит одно поле int (4 байта)
	static_assert(sizeof(Entity) == 1 * sizeof(int));

    entity.test_v1();
	entity.test_v2();
//  entity.test_v3(); // ОШИБКА! test_v3() защищен (protected)

	// Создание объекта производного класса
	// Порядок вызова: Entity(1) → инициализация m_y → тело Client
	Client client(1, 1);

	// Client содержит: m_x (от Entity) + m_y (от Client) = 8 байт
	// В памяти базовая часть ВСЕГДА ПЕРВАЯ!
	static_assert(sizeof(Client) == 2 * sizeof(int));

	// Вызов унаследованного метода (не переопределен в Client)
	client.test_v1();  // Выведет: "Entity::test_v1"

	// Вызов переопределенного метода (name hiding)
	client.test_v2();  // Выведет: "Client::test_v2", затем "Entity::test_v2"

	// Вызов protected метода, сделанного public через using
	client.test_v3();  // Выведет: "Entity::test_v3"
}

