#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace hydro::scene
{
	Scene::Scene(std::string name)
		:
		name_(name)
	{}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity e = { registry_.create(), this };
		e.AddComponent<TagComponent>(name);
		return e;
	}
}