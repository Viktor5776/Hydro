#pragma once
#include "Entity.h"
#include "../ioc/Container.h"
#include "ComponentStore.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <typeinfo>

namespace hydro::ecs
{
	class Ecs
	{
	public:
		Entity createEntity()
		{
			uint32_t id;
			if (!freeIds.empty()) {
				id = freeIds.back();
				freeIds.pop_back();
			}
			else {
				id = nextId++;
			}
			
			Entity e = Entity(id);
			entitys.push_back(e);
			return e;
		}

		void destroyEntity(Entity e)
		{
			if (entityComponentMap.contains(e.getId())) {
				for (const auto& type : entityComponentMap[e.id]) {
					componentStores[type]->remove(e);
				}
				entityComponentMap.erase(e.getId());
			}
			std::erase(entitys, e);
			freeIds.push_back(e.getId());
		}

		template<typename T>
		void addComponent(Entity e, T c)
		{
			auto typeId = std::type_index(typeid(T));
			if (!componentStores.contains(typeId)) {
				componentStores[typeId] = std::make_unique<ComponentStore<T>>();
			}

			static_cast<ComponentStore<T>*>(componentStores[typeId].get())->add(Entity{ e.getId() }, c);
			entityComponentMap[e.getId()].insert(typeId);
		}

		template<typename T>
		void addComponent(Entity e)
		{
			auto typeId = std::type_index(typeid(T));
			if (!componentStores.contains(typeId)) {
				componentStores[typeId] = std::make_unique<ComponentStore<T>>();
			}

			static_cast<ComponentStore<T>*>(componentStores[typeId].get())->add(Entity{ e.getId() });
			entityComponentMap[e.getId()].insert(typeId);
		}

		template<typename T>
		std::shared_ptr<T> getComponent(Entity e)
		{
			auto typeId = std::type_index(typeid(T));
			auto it = componentStores.find(typeId);
			if (it == componentStores.end()) return nullptr;
			return static_cast<ComponentStore<T>*>(it->second.get())->get(Entity{ e.getId() });
		}

		template<typename T>
		void removeComponent(Entity e)
		{
			auto typeId = std::type_index(typeid(T));
			auto it = componentStores.find(typeId);
			if (it != componentStores.end()) {
				it->second->remove(Entity{ e.getId() });
				entityComponentMap[e.getId()].erase(typeId);
			}
		}

		template<typename T>
		bool hasComponent(Entity e) const {
			auto typeId = std::type_index(typeid(T));
			auto it = componentStores.find(typeId);
			if (it == componentStores.end()) return false;
			return it->second->has(e);
		}
	private:
		uint32_t nextId = 1;
		std::vector<uint32_t> freeIds;
		std::vector<Entity> entitys;

		std::unordered_map<std::type_index, std::unique_ptr<IComponentStore>> componentStores;
		std::unordered_map<uint32_t, std::unordered_set<std::type_index>> entityComponentMap;
	};
}