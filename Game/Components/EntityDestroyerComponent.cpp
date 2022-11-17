#include "Game/pch.h"
#include "EntityDestroyerComponent.h"

EntityDestroyerComponent::EntityDestroyerComponent(EntityID entity)
    : myEntityToDestroy(entity)
{
}

void EntityDestroyerComponent::DestroyEntity() const
{
    auto ecs = EntityComponentManager::GetInstance();

    ecs->MarkForDestruction(myEntityToDestroy);
}
