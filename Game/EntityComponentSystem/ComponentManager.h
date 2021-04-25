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

struct ComponentWithType{
    Component* component;
    ComponentType type;
};

typedef size_t EntityID;
typedef std::vector<ComponentWithType> ComponentWithTypeList;

class EntityComponentManager:public Singleton<EntityComponentManager>
{
public:
    friend Singleton<EntityComponentManager>;

    EntityID CreateEntity();
    void DestroyEntity(EntityID entityID);
    bool IsEntityValid(EntityID entityID);

    template<class T, class... Args>
    T* CreateComponent(EntityID entityID, Args&&... args)
    {
        if (!IsEntityValid(entityID))
        {
            // [LOG] passed invalid entityID
            return nullptr;
        }

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
                componentPtr->SetEntity(entityID);
                m_Entities[entityID].push_back({ componentPtr, type });

                return componentPtr;
            }
        }

        return nullptr;
    }

    template<class T>
    T* GetComponent(EntityID entityID)
    {
        return static_cast<T*>(GetComponent(entityID, T::GetStaticType()));
    }

    Component* GetComponent(EntityID entityID, ComponentType componentType);

    void Update(float dt);
    
private:
    EntityComponentManager();
    ~EntityComponentManager() = default;

    void DestroyComponent(Component* componentPtr);

    PoolAllocator* CreateComponentPool(ComponentType type, size_t numberOfObjects, size_t objectSize);

    std::unordered_map<ComponentType, PoolAllocator> m_PoolAllocatorsMap;
    std::vector<ComponentWithTypeList> m_Entities;
    LinearAllocator m_MainAllocator;
    EntityID m_EntityGenerator = 0u;
};
