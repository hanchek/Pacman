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

bool EntityComponentManager::IsEntityValid(EntityID entityID) const
{
    return myRegistry.valid(entityID);
}
