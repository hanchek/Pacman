#pragma once

#include <unordered_map>
#include <memory>

#include "ComponentType.h"
#include "Component.h"
#include "Game/Allocators/PoolAllocator.h"
#include "Game/Allocators/LinearAllocator.h"
#include "Game/Allocators/FreeListAllocator.h"
#include "Game/Singleton.h"


class Component;

class ComponentManager:public Singleton<ComponentManager>
{
public:
    friend class Singleton<ComponentManager>;

    template<class T, class... Args>
    T* CreateComponent(Args&&... args)
    {
        const ComponentType type = T::GetStaticType();

        const auto foundIt = m_PoolAllocatorsMap.find(type);
        PoolAllocator* componentPool = nullptr;
        if (foundIt != m_PoolAllocatorsMap.end())
        {
            componentPool = &foundIt->second;
        }
        else
        {
            componentPool = CreateComponentPool(type, 100, sizeof(T));
        }

        if (componentPool)
        {
            void* allocatedMemory = componentPool->Allocate();
            if (allocatedMemory != nullptr)
            {
                // placement new 
                T* componentPtr = new (allocatedMemory) T(args...);
                return componentPtr;
            }
        }

        return nullptr;
    }

    void DestroyComponent(Component* componentPtr);
    
private:
    ComponentManager();
    ~ComponentManager() = default;

    PoolAllocator* CreateComponentPool(ComponentType type, size_t numberOfObjects, size_t objectSize);

    std::unordered_map<ComponentType, PoolAllocator> m_PoolAllocatorsMap;
    LinearAllocator m_MainAllocator;
};
