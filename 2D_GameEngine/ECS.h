#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// inline functions:
// Using the inline keyword in front of a function will ask the
// compiler to insert the whole code of the function into the point
// of the inline function call. Basically, it *can* decrease the overhead
// performance cost of calling a function *if* the logic in the function is
// short. This is primarily used in situations where a small function is being
// called many times.

// noexept
// Specifies that the function will not throw any exceptions. This is used to 
// *potentially* gain performance from compiler optimizations.

// constexpr
// Similer to const, it can be applied to variables so that a compiler error will
// be thrown if any code attempts to modify the value. Unlike const, it can also be
// applied to functions and class constructors. It indicates that the value, or return
// value is constant and, if possible, will be computed at compile time. If the value
// can be computed at compile time vs run time, it can help the program run faster
// and use less memory. (another optimization)

// virtual function
// A virtual function is a member function that you expect to be redefined in derived
// classes. When you refer to a derived class object using a pointer or reference to
// the base class, you can call a virtual function for that object and execute the 
// derived classes version of that function.

// vector
// Basicly an array of dynamic size.

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId getComponentTypeId()
{
	static ComponentId lastId = 0;
	return lastId++;
}

template <typename T> inline ComponentId getComponentTypeId() noexcept
{
	static ComponentId typeId = getComponentTypeId();
	return typeId;
}

// max components that an entity is able to hold
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
	Entity *Entity;
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool _active = true;
	std::vector<std::unique_ptr<Component>> _components;

	ComponentArray _componentArray;
	ComponentBitSet _componentBitSet;
public:
	void Update()
	{
		// foreach loop: for each item in components, call the update,
		// and draw functions.
		for (auto &c : _components) c->Update();
		for (auto &c : _components) c->Draw();
	}

	void Draw() {}
	bool const IsActive() { return _active; }
	void Destroy() { _active = false; }
	
	template <typename T> bool HasComponent() const
	{
		return _componentBitSet[getComponentTypeId<T>];
	}

	template <typename T, typename... TArgs> 
	T& AddComponent(TArgs&&... mArgs)
	{
		T *c(new T(std::forward<TArgs>(mArgs)...));
		c->Entity = this;
		std::unique_ptr<Component> uPtr(c);
		_components.emplace_back(std::move(uPtr));

		_componentArray[getComponentTypeId<T>()] = c;
		_componentBitSet[getComponentTypeId<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(_componentArray[getComponentTypeId<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> _entities;

public:
	void Update()
	{
		for (auto& e : _entities) e->Update();
	}

	void Draw()
	{
		for (auto& e : _entities) e->Draw();
	}

	void Refresh()
	{
		_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities), 
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->IsActive();
		}), std::end(_entities));
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr(e);
		_entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
