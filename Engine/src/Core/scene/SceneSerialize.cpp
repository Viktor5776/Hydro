#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include <nlohmann\json.hpp>
#include <fstream>
#include <format>
#include <string>

//Serelize helpers
template<>
struct std::formatter<glm::vec3> : std::formatter<std::string> {
	auto format(const glm::vec3& v, format_context& ctx) const {
		return std::formatter<std::string>::format(
			std::format("{} {} {}", v.x, v.y, v.z), ctx
		);
	}
};


//Deserelize helpers
template<typename T>
T FromString(std::string str)
{}

template<>
glm::vec3 FromString(std::string str)
{
	glm::vec3 result;

	std::istringstream iss(str);
	iss >> result.x;
	iss >> result.y;
	iss >> result.z;

	return result;
}



namespace hydro::scene
{

	static void SerializeEntity(nlohmann::json& out, Entity& entity)
	{
		nlohmann::json entityOut;

		if (entity.HasComponents<TagComponent>()) {
			const auto& tag = entity.GetComponent<TagComponent>();
			entityOut["Tag"] = tag.Tag;
		}

		if (entity.HasComponents<Transform>()) {
			const auto& transform = entity.GetComponent<Transform>();
			entityOut["Transform"]["Translation"] = std::format("{}", transform.Translation);
			entityOut["Transform"]["Rotation"] = std::format("{}", transform.Rotation);;
			entityOut["Transform"]["Scale"] = std::format("{}", transform.Scale);;
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
				if (!entityJson.contains("Tag") || !entityJson.contains("Transform")) {
					continue;
				}
					
				Entity entity = CreateEntity(entityJson["Tag"].get<std::string>());
				entity.AddComponent<Transform>(
					FromString<glm::vec3>(entityJson["Transform"]["Translation"]),
					FromString<glm::vec3>(entityJson["Transform"]["Rotation"]),
					FromString<glm::vec3>(entityJson["Transform"]["Scale"])
				);

				//More components goes here
			}
		}
		
		return true;
	}
}