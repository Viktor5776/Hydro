#pragma once
#include <entt\entt.hpp>

#include <string>
#include <filesystem>

namespace hydro::scene
{
	class Entity;

	class Scene
	{
	public:
		Scene(std::string name);
		~Scene();
		Entity CreateEntity(const std::string& name = "");

		template<typename... Components>
		auto GetAllEntitysWith()
		{
			return registry_.view<Components...>();
		}
	private:
		void Serialize(std::filesystem::path path);
		bool Deserialize(std::filesystem::path path);
	private:
		entt::registry registry_;
		std::string name_;

		friend Entity;
	};
	
}