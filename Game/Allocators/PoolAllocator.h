#pragma once
#include <vector>

class PoolAllocator
{
public:
    PoolAllocator(size_t size, void* data, size_t objectSize);

    void* Allocate();
    void Free(void* data);
    void Clear();

    std::vector<void*> GetObjects()
    {
        std::vector<void*> allocatedObjects;
        for (const auto& poolEntry : m_ObjectPool)
        {
            if (!poolEntry.isFree)
            {
                allocatedObjects.push_back(poolEntry.data);
            }
        }

        return allocatedObjects;
    }

private:
    struct PoolEntry
    {
        void* const data;
        bool isFree;
    };
    std::vector<PoolEntry> m_ObjectPool;
    size_t m_ObjectSize = 0u;
};
