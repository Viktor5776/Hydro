#pragma once
#include "Scene.h"
#include "../utl/Assert.h"
#include "Components.h"

namespace hydro::scene
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			hass(!HasComponents<T>()).msg(L"Entity has component!");
			return scene_->registry_.emplace<T>(entityHandle_, std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			return scene_->registry_.emplace_or_replace<T>(entityHandle_, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			hass(HasComponents<T>()).msg(L"Entity does not have component!");
			return scene_->registry_.get<T>(entityHandle_);
		}

		template<typename... T>
		bool HasComponents()
		{
			return scene_->registry_.all_of<T...>(entityHandle_);
		}

		template<typename T>
		void RemoveComponent()
		{
			hass(HasComponents<T>()).msg(L"Entity does not have component!");
			scene_->registry_.remove<T>(entityHandle_);
		}

		operator bool() const { return entityHandle_ != entt::null; }
		operator entt::entity() const { return entityHandle_; }

		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		bool operator==(const Entity& other) const
		{
			return entityHandle_ == other.entityHandle_ && scene_ == other.scene_;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity entityHandle_ = entt::null;
		Scene* scene_ = nullptr;
	};
}