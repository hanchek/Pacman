#include "EntityComponentManager.h"

EntityID NewEntityComponentManager::CreateEntity()
{
    return myRegistry.create();
}

void NewEntityComponentManager::DestroyEntity(EntityID entityID)
{
    myRegistry.destroy(entityID);
}

bool NewEntityComponentManager::IsEntityValid(EntityID entityID) const
{
    return myRegistry.valid(entityID);
}
