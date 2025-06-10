#include "Entity.h"

namespace hydro::scene
{

	Entity::Entity(entt::entity handle, Scene* scene)
		:
		entityHandle_(handle),
		scene_(scene)
	{}

}