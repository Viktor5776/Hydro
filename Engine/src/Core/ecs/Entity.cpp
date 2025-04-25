#include "Entity.h"

namespace hydro::ecs
{
    Entity::Entity(uint32_t id)
        :
        id(id)
    {}

    bool Entity::operator==(const Entity& other) const
    {
        return id == other.id;
    }

    uint32_t Entity::getId() const
    {
        return id;
    }
}