// ПРИВАТНОЕ НАСЛЕДОВАНИЕ vs КОМПОЗИЦИЯ
// Демонстрирует: различия между private inheritance и composition

#include <print>

// БАЗОВЫЙ КЛАСС Entity (пустой класс - только методы, нет полей)
class Entity
{
public :
	void test_v1() const 
	{ 
		std::print("Entity::test_v1\n");
	}

protected :
	// Защищенный метод - доступен в наследниках, но НЕ при композиции
	void test_v2() const 
	{ 
		std::print("Entity::test_v2\n");
	}
};

// Server_v1 - ПРИВАТНОЕ НАСЛЕДОВАНИЕ (PRIVATE INHERITANCE)
// private Entity - все public и protected члены становятся private
// Семантика: "Server_v1 реализован через Entity" (is-implemented-in-terms-of)
// ПРЕИМУЩЕСТВО: доступ к protected членам базового класса
class Server_v1 : private Entity
{
public :
	void test() const
	{
		// Внутри класса можем вызывать методы базового класса
		// Даже если они стали private для внешнего мира
		Entity::test_v1(); // OK

		// Доступ к protected методу - это КЛЮЧЕВОЕ отличие от композиции!
		Entity::test_v2(); // OK (при композиции было бы ОШИБКОЙ!)
	}
};

// Server_v2 - КОМПОЗИЦИЯ (COMPOSITION)
// Entity m_entity - объект как поле класса
// Семантика: "Server_v2 СОДЕРЖИТ Entity" (HAS-A relationship)
// ПРЕИМУЩЕСТВО: более явно и просто, лучше инкапсуляция
class Server_v2 
{
public :
	void test() const
	{
		// Доступ к публичному методу через объект-член
		m_entity.test_v1(); // OK: test_v1() публичен

	//	m_entity.test_v2(); // ОШИБКА! test_v2() protected - недоступен при композиции
	}

private : 
	// Объект Entity как приватное поле - композиция
	Entity m_entity;
};

int main()
{
	Server_v1 server_v1;

//	server_v1.test_v1(); // ОШИБКА! test_v1() стал private из-за private наследования
//	server_v1.test_v2(); // ОШИБКА! test_v2() стал private

	// Вызов публичного метода - внутри вызываются методы Entity
	server_v1.test();  // Выведет: "Entity::test_v1" и "Entity::test_v2"

	Server_v2 server_v2;

//	server_v2.test_v1(); // ОШИБКА! test_v1() - метод Entity, не Server_v2
//	server_v2.test_v2(); // ОШИБКА! test_v2() - метод Entity, не Server_v2

	// Вызов публичного метода - внутри вызывается m_entity.test_v1()
	server_v2.test();  // Выведет: "Entity::test_v1"
}

// РЕЗЮМЕ РАЗЛИЧИЙ:
// ПРИВАТНОЕ НАСЛЕДОВАНИЕ:
//   + Доступ к protected членам
//   + Empty Base Optimization (экономия памяти для пустых классов)
//   + Можно переопределять виртуальные функции
//   - Менее явно (не видно, что используется Entity)
//
// КОМПОЗИЦИЯ:
//   + Более явно и просто
//   + Лучше инкапсуляция
//   - НЕТ доступа к protected членам
//   - НЕТ Empty Base Optimization
//
// ПРАВИЛО: Prefer composition over private inheritance
//          (Предпочитайте композицию приватному наследованию)

