#pragma once

#include "ComponentType.h"

#define DEFINE_COMPONENT_NAME(TYPE)\
    static ComponentType GetStaticType() { return ComponentType::TYPE; }\
    ComponentType GetType() override { return TYPE::GetStaticType(); }\

class Component
{
public:
    virtual ~Component() = default;
    static ComponentType GetStaticType() { return ComponentType::Component; }
    virtual ComponentType GetType() { return GetStaticType(); }

private:

};
