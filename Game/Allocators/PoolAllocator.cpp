#include "PoolAllocator.h"

#include <cassert>

PoolAllocator::PoolAllocator(size_t size, void* data, size_t objectSize)
{
    assert((size % objectSize) == 0 && "Size should be multiple of objectSize");

    const size_t objectsNumber = size / objectSize;
    m_ObjectPool.reserve(objectsNumber);

    union
    {
        void* asVoidPtr;
        std::byte* asBytePtr;
    };

    asVoidPtr = data;

    for (int i = 0; i < objectsNumber; ++i)
    {
        m_ObjectPool.push_back({ asVoidPtr, true });
        asBytePtr += objectSize;
    }
}

void* PoolAllocator::Allocate()
{
    auto foundIt = std::find_if(m_ObjectPool.begin(), m_ObjectPool.end(),
        [](const PoolEntry& entry)
        {
            return entry.isFree;
        }
    );

    if (foundIt != m_ObjectPool.end())
    {
        foundIt->isFree = false;
        return foundIt->data;
    }

    return nullptr;
}

void PoolAllocator::Free(void* data)
{
    const auto foundIt = std::find_if(m_ObjectPool.begin(), m_ObjectPool.end(),
        [data](const PoolEntry& entry)
        {
            return entry.data == data;
        }
    );

    if (foundIt == m_ObjectPool.end())
    {
        assert(false && "Tried to free data that is not in allocated pool");
        return;
    }

    foundIt->isFree = true;
}

void PoolAllocator::Clear()
{
    for (int i = 0; i < m_ObjectPool.size(); ++i)
    {
        m_ObjectPool[i].isFree = true;
    }
}
