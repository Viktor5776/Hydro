#pragma once
#include "Entity.h"
#include "../ioc/Container.h"
#include "ComponentStore.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <typeinfo>
#include <algorithm>
#include <ranges>

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

		template<IsComponent T>
		void addComponent(Entity e, T c)
		{
			auto typeId = std::type_index(typeid(T));
			if (!componentStores.contains(typeId)) {
				componentStores[typeId] = std::make_unique<ComponentStore<T>>();
			}

			auto store = static_cast<ComponentStore<T>*>(componentStores[typeId].get());
			store->add(e, c);
			
			entityComponentMap[e.getId()].insert(typeId);

			if constexpr (std::is_base_of_v<IScript, T>) {
				scripts.push_back(store->get(e).get());
			}
		}

		template<IsComponent T>
		void addComponent(Entity e)
		{
			auto typeId = std::type_index(typeid(T));
			if (!componentStores.contains(typeId)) {
				componentStores[typeId] = std::make_unique<ComponentStore<T>>();
			}

			ComponentStore<T>* store = static_cast<ComponentStore<T>*>(componentStores[typeId].get());
			store->add(e);

			entityComponentMap[e.getId()].insert(typeId);

			if constexpr (std::is_base_of_v<IScript, T>) {
				scripts.push_back(store->get(e).get());
			}
		}

		template<IsComponent T>
		std::shared_ptr<T> getComponent(Entity e)
		{
			auto typeId = std::type_index(typeid(T));
			auto it = componentStores.find(typeId);
			if (it == componentStores.end()) return nullptr;
			return static_cast<ComponentStore<T>*>(it->second.get())->get(Entity{ e.getId() });
		}

		template<IsComponent T>
		void removeComponent(Entity e)
		{
			auto typeId = std::type_index(typeid(T));
			auto it = componentStores.find(typeId);
			if (it != componentStores.end()) {
				it->second->remove(Entity{ e.getId() });
				entityComponentMap[e.getId()].erase(typeId);
			}

			if constexpr (std::is_base_of_v<IScript, T>) {
				auto ptr = static_cast<ComponentStore<T>*>(it->second.get())->get(e).get();
				std::erase(scripts, ptr);
			}
		}

		template<IsComponent T>
		bool hasComponent(Entity e) const {
			auto typeId = std::type_index(typeid(T));
			auto it = componentStores.find(typeId);
			if (it == componentStores.end()) return false;
			return it->second->has(e);
		}

		template<IsComponent... Ts>
		auto view() {
			return entitys | std::ranges::views::filter([](Entity e) {return (e.hasComponent<Ts>() && ...); });
		}

		std::vector<IScript*> GetScripts() {
			return scripts;
		}
	private:
		uint32_t nextId = 1;
		std::vector<uint32_t> freeIds;
		std::vector<Entity> entitys;
		std::vector<IScript*> scripts;

		std::unordered_map<std::type_index, std::unique_ptr<IComponentStore>> componentStores;
		std::unordered_map<uint32_t, std::unordered_set<std::type_index>> entityComponentMap;
	};
}