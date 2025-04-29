#pragma once
#include "Entity.h"
#include <unordered_map>

namespace hydro::ecs
{
	class IComponentStore {
	public:
		virtual ~IComponentStore() = default;
		virtual void remove(Entity e) = 0;
		virtual bool has(Entity e) const = 0;
	};

	template<typename T>
	class ComponentStore : public IComponentStore {
	public:
		void add(Entity e, const T& component) {
			components[e.getId()] = component;
		}

		void add(Entity e) {
			components[e.getId()] = T();
		}

		std::shared_ptr<T> get(Entity e) {
			auto it = components.find(e.getId());
			return it != components.end() ? std::make_shared<T>(it->second) : nullptr;
		}

		void remove(Entity e) override {
			components.erase(e.getId());
		}

		bool has(Entity e) const override {
			return components.contains(e.getId());
		}
	private:
		std::unordered_map<uint32_t, T> components;
	};
}