#include "Game/pch.h"
#include "EntityComponentManager.h"

EntityID EntityComponentManager::CreateEntity()
{
    return myRegistry.create();
}

void EntityComponentManager::DestroyEntity(EntityID entityID)
{
    myRegistry.destroy(entityID);
}

void EntityComponentManager::MarkForDestruction(EntityID entityID)
{
    myEntitiesToDestroy.push_back(entityID);
}

bool EntityComponentManager::DestroyMarkedEntities()
{
    if (myEntitiesToDestroy.empty())
    {
        return false;
    }

    for (EntityID entityID: myEntitiesToDestroy)
    {
        DestroyEntity(entityID);
    }

    myEntitiesToDestroy.clear();

    return true;
}

bool EntityComponentManager::IsEntityValid(EntityID entityID) const
{
    return myRegistry.valid(entityID);
}
