#pragma once

#include "ComponentType.h"
#include "ComponentManager.h"

#define DEFINE_COMPONENT_NAME(TYPE)\
    static ComponentType GetStaticType() { return ComponentType::TYPE; }\
    ComponentType GetType() override { return TYPE::GetStaticType(); }\

typedef size_t EntityID;

class Component
{
public:
    virtual ~Component() = default;
    static ComponentType GetStaticType() { return ComponentType::Component; }
    virtual ComponentType GetType() { return GetStaticType(); }

    virtual void Update(float dt) {};

    void SetEntity(EntityID entityID) { m_EntityID = entityID; }

protected:
    EntityID m_EntityID = -1;

private:

};
