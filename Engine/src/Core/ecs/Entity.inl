#pragma once
#include "Ecs.h"
#include "../ioc/Singletons.h"

namespace hydro::ecs
{

    template<typename T>
    void Entity::addComponent()
    {
        ioc::Sing().Resolve<Ecs>()->template addComponent<T>(*this);
    }

    template<typename T>
    void Entity::addComponent(const T& component)
    {
        ioc::Sing().Resolve<Ecs>()->template addComponent<T>(*this, component);
    }

    template<typename T>
    std::shared_ptr<T> Entity::getComponent()
    {
        return ioc::Sing().Resolve<Ecs>()->template getComponent<T>(*this);
    }

    template<typename T>
    void Entity::removeComponent()
    {
        ioc::Sing().Resolve<Ecs>()->template removeComponent<T>(*this);
    }

    template<typename T>
    bool Entity::hasComponent()
    {
        return ioc::Sing().Resolve<Ecs>()->template hasComponent<T>(*this);
    }
}