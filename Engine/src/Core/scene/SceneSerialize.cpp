#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include <nlohmann\json.hpp>
#include <fstream>

namespace hydro::scene
{
	static void SerializeEntity(nlohmann::json& out, Entity& entity)
	{
		nlohmann::json entityOut;

		if (entity.HasComponents<TagComponent>()) {
			const auto& tag = entity.GetComponent<TagComponent>();
			entityOut["Tag"] = tag.Tag;
		}

		//More components goes here

		out["Entities"].push_back(entityOut);
	}

	void Scene::Serialize(std::filesystem::path path)
	{
		nlohmann::json out;

		out["Scene"] = name_;
		out["Entities"] = nlohmann::json::array();
		
		for (auto e : registry_.view<entt::entity>()) {
			Entity entity = { e,this };
			if (!entity) {
				continue;
			}

			SerializeEntity(out, entity);
		}

		std::ofstream fileOut(path);
		fileOut << std::setw(4) << out;
	}

	bool Scene::Deserialize(std::filesystem::path path)
	{
		registry_.clear();

		std::ifstream fileIn(path);
		if (!fileIn.is_open())
			return false;

		nlohmann::json in;
		fileIn >> in;

		if (!in.contains("Scene")) {
			return false;
		}

		name_ = in["Scene"];

		if (in.contains("Entities")) {

			for (const auto& entityJson : in["Entities"]) {
				if (!entityJson.contains("Tag")) {
					continue;
				}
					
				Entity entity = CreateEntity(entityJson["Tag"].get<std::string>());

				//More components goes here
			}
		}
		
		return true;
	}
}