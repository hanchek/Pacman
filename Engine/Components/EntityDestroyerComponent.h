#pragma once

#include "EntityComponentSystem/EntityComponentManager.h"

class EntityDestroyerComponent
{
public:
    EntityDestroyerComponent(EntityID entity);
    
    void DestroyEntity() const;

private:
    EntityID myEntityToDestroy;
};