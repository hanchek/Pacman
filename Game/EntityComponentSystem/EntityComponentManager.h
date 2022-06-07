#pragma once

#include <entt/entity/registry.hpp>

#include "Game/Singleton.h"

using EntityID = entt::entity;

template<typename... ComponentType>
using ComponentsIterable = entt::basic_view<EntityID, entt::get_t<ComponentType...>, entt::exclude_t<>>;

class EntityComponentManager : public Singleton<EntityComponentManager>
{
public:
    friend Singleton<EntityComponentManager>;

    EntityID CreateEntity();
    void DestroyEntity(EntityID entityID);
    bool IsEntityValid(EntityID entityID) const;

    template<typename T, typename... Args>
    decltype(auto) CreateComponent(EntityID entityID, Args&&... args)
    {
        return myRegistry.emplace<T>(entityID, std::forward<Args>(args)...);
    }

    template<typename T>
    T* GetComponent(EntityID entityID)
    {
        return myRegistry.try_get(entityID);
    }

    template<typename ComponentType>
    EntityID GetEntity(const ComponentType& component) const
    {
        return entt::to_entity(myRegistry, component);
    }
    
    template<typename ComponentType, typename... Others>
    ComponentsIterable<ComponentType, Others...> GetComponentsIterable()
    {
        return myRegistry.view<ComponentType, Others...>();
    }

    template<typename ComponentType, typename... Others, typename Func>
    void ForEachComponent(Func func)
    {
        GetComponentsIterable<ComponentType, Others...>().each(func);
    }

private:
    entt::registry myRegistry;

    EntityComponentManager() = default;
    ~EntityComponentManager() = default;
};
