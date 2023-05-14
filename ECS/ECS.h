//
// Created by Андрей on 03.05.2023.
//

#ifndef PROJECTS_2023_1_ECHPOCHMAKI_ECS_BASICENTITY_H_
#define PROJECTS_2023_1_ECHPOCHMAKI_ECS_BASICENTITY_H_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "../map_generation/IRoomGenerator.h"
#include "Tile.h"
#include <stdexcept>

class Component;
class Entity;

using ComponentID = std::size_t;
using TimeValueType = double;

class EntityCreator {
public:
    std::vector<Entity*> createEntitiesByMap(const tileMap& tilemap){return std::vector<Entity*>();}
};


inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}


constexpr std::size_t
maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
 public:
	Entity* entity;

	virtual void Init()
	{
		entity = nullptr;
	}
	virtual void Update(TimeValueType timePassed)
	{
	}
	virtual void Draw()
	{
	}

	virtual ~Component()
	{
	}
};




class Entity
{
 public:
	int id;

	bool IsActive() const
	{
		return active;
	}
	void Destroy()
	{
		active = false;
	}

	template<typename T>
	bool HasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}



	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&& ... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		return *c;
	}

	template<typename T>
	T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
        if (ptr == nullptr)
        {
            throw std::runtime_error(std::string{"Has no component: "} + typeid(T).name());
        }


		return *static_cast<T*>(ptr);
	}

	template<typename... TArgs>
	bool HasComponents() const
	{
		//set<>
		/*std::vector<bool> componentIsContained{ HasComponent<TArgs>()...};
		for (bool contains : componentIsContained)
			if (!contains)
				return false;
		return true;*/
		return (componentBitSet[getComponentTypeID<TArgs>()] && ...); //TODO::make several contents choice
	}

	template<typename T>
	bool RemoveComponent() const
	{
		if (!componentBitSet[getComponentTypeID<T>()]) //Component already deleted
			return false;
		components[getComponentTypeID<T>()].reset();
		componentBitSet[getComponentTypeID<T>()] = true;
	}




 private:

	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};


#endif //PROJECTS_2023_1_ECHPOCHMAKI_ECS_BASICENTITY_H_
