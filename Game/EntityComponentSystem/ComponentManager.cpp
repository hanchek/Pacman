#include "ComponentManager.h"

constexpr size_t memoryForComponents = 1024u * 1024u;
constexpr size_t numberOfComponentes = 100u;
constexpr size_t DEFAULT_SIZE_OF_POOL = 1024u * 1024u;

EntityComponentManager::EntityComponentManager() : m_MainAllocator(memoryForComponents * static_cast<size_t>(ComponentType::Count))
{

}

EntityID EntityComponentManager::CreateEntity()
{
    EntityID newEntityID = m_Entities.size();
    // create empty vector of components
    m_Entities.push_back({});

    return newEntityID;
}

void EntityComponentManager::DestroyEntity(EntityID entityID)
{
    if (!IsEntityValid(entityID))
    {
        // [LOG] passed invalid entityID
        return;
    }

    for (auto& componentWithType : m_Entities[entityID])
    {
        DestroyComponent(componentWithType.component);
    }

    m_Entities[entityID].clear();
}

bool EntityComponentManager::IsEntityValid(EntityID entityID)
{
    return entityID < m_Entities.size();
}

Component* EntityComponentManager::GetComponent(EntityID entityID, ComponentType componentType)
{
    if (!IsEntityValid(entityID))
    {
        // [LOG] passed invalid entityID
        return nullptr;
    }

    ComponentWithTypeList& entityComponents = m_Entities[entityID];
    auto foundIt = std::find_if(entityComponents.begin(), entityComponents.end(), [componentType](ComponentWithType& component)
        {
            return componentType == component.type;
        }
    );

    if (foundIt != entityComponents.end())
    {
        return foundIt->component;
    }

    return nullptr;
}

void EntityComponentManager::DestroyComponent(Component* componentPtr)
{
    if (componentPtr)
    {
        const ComponentType type = componentPtr->GetType();
        const auto foundIt = m_PoolAllocatorsMap.find(type);
        if (foundIt != m_PoolAllocatorsMap.end())
        {
            componentPtr->~Component();
            foundIt->second.Free(componentPtr);
        }
        else
        {
            // [LOG] Possible memory leak
        }
    }
    else
    {
        // [LOG] Passed nullptr to ComponentManager::DestroyComponent
    }
}

PoolAllocator* EntityComponentManager::CreateComponentPool(ComponentType type, size_t numberOfObjects, size_t objectSize)
{
    auto foundIt = m_PoolAllocatorsMap.find(type);
    if (foundIt != m_PoolAllocatorsMap.end())
    {
        // [LOG] Tried to second create
        return &(foundIt->second);
    }
    else
    {
        const size_t memorySize = numberOfObjects * objectSize;
        void* memoryForPool = m_MainAllocator.Allocate(memorySize);
        if (memoryForPool)
        {
            auto insertResult = m_PoolAllocatorsMap.insert({ type, PoolAllocator(memorySize, memoryForPool, objectSize) });
            const auto& a = insertResult.first;
            return &a->second;
        }    
    }

    return nullptr;
}
