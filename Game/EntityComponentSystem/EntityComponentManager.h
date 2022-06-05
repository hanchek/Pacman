#pragma once

#include <entt/entity/helper.hpp>
#include <entt/entity/registry.hpp>

#include "Game/Singleton.h"

using EntityID = entt::entity;
using UpdateTask = std::function<void(float dt, entt::registry& reg)>;

namespace sf
{
    class RenderWindow;
}

class NewEntityComponentManager : public Singleton<NewEntityComponentManager>
{
public:
    friend Singleton<NewEntityComponentManager>;

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

    void AddUpdateTask(UpdateTask task);

    void Update(float dt);

    void Render(sf::RenderWindow& window);

private:
    entt::registry myRegistry;
    std::vector<UpdateTask> myTasks;

    NewEntityComponentManager() = default;
    ~NewEntityComponentManager() = default;
};
