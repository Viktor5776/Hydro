#pragma once
#include <cstdint>
#include <memory>

namespace hydro::ecs
{
	class Ecs;

	class Entity
	{
	public:
		bool operator==(const Entity& other) const;
		template<typename T>
		void addComponent();

		template<typename T>
		void addComponent(const T& component);

		template<typename T>
		std::shared_ptr<T> getComponent();

		template<typename T>
		void removeComponent();

		template<typename T>
		bool hasComponent();

		uint32_t getId() const;
	private:
		Entity(uint32_t id);
	private:
		uint32_t id;
		friend class Ecs;
	};
}

#include "Entity.inl"