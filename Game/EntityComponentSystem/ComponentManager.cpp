#include "ComponentManager.h"

constexpr size_t memoryForComponents = 1024u * 1024u;
constexpr size_t numberOfComponentes = 100u;
constexpr size_t DEFAULT_SIZE_OF_POOL = 1024u * 1024u;

ComponentManager::ComponentManager() : m_MainAllocator(memoryForComponents * static_cast<size_t>(ComponentType::Count))
{

}

void ComponentManager::DestroyComponent(Component* componentPtr)
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

PoolAllocator* ComponentManager::CreateComponentPool(ComponentType type, size_t numberOfObjects, size_t objectSize)
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
