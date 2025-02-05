#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "Mouse.h"

class Mouse;

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32; //groups = layers

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {} //functions that are going to be overridden
	virtual void update() {}
	virtual void updateButton(Mouse& mouse, std::string tag, int x) {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity //keeps a list of all Components
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	std::string tag;
	Entity(Manager& memberManager) : manager(memberManager){}

	void update()
	{
		for (auto& c : components) c->update();
		
	}
	void draw() 
	{
		for (auto& c : components) c->draw();
	}

	void updateButton(Mouse& mouse, std::string tag, int x)
	{
		for (auto& c : components) c->updateButton(mouse, tag, x);
	}

	bool isActive()
	{
		return active;
	}
	void destroy()
	{
		active = false;
	}

	bool hasGroup(Group memberGroup)
	{
		return groupBitSet[memberGroup];
	}
	void addGroup(Group memberGroup);
	void deleteGroup(Group memberGroup)
	{
		groupBitSet[memberGroup] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;

	}

	template<typename T> 
	T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);

	}

};

class Manager //keeps a list of all Entities
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void updateButton(Mouse& mouse, std::string tag, int x)
	{
		for (auto& e : entities) e->updateButton(mouse, tag, x);
	}

	void refresh() //removes entities if they are not active
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* memberEntity)
				{
					return !memberEntity->isActive() || !memberEntity->hasGroup(i);
				}
			),
				std::end(v));
		}//^ removes entities from the groups before updating them

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void addToGroup(Entity* memberEntity, Group memberGroup)
	{
		groupedEntities[memberGroup].emplace_back(memberEntity);
	}//add entity to group

	std::vector<Entity*>& getGroup(Group memberGroup)
	{
		return groupedEntities[memberGroup];
	}//makes a list of all entities in a group

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e }; //assign unique pointer to each new entity
		entities.emplace_back(std::move(uPtr)); //add to entity list
		return *e;
	}

	Entity& addEntity(std::string t)
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e }; //assign unique pointer to each new entity
		entities.emplace_back(std::move(uPtr)); //add to entity list
		e->tag = t;
		return *e;
	}
};


