#include "FreeListAllocator.h"

#include <cassert>

FreeListAllocator::FreeListAllocator(size_t size, void* data)
{
    m_FreeList.push_back({ size, data, true });
}

void* FreeListAllocator::Allocate(size_t size)
{
    const auto foundIt = std::find_if(m_FreeList.begin(), m_FreeList.end(),
        [size](const ListEntry& entry)
        {
            return entry.isFree && entry.size >= size;
        }
    );

    if (foundIt != m_FreeList.end())
    {
        const size_t sizeDiff = foundIt->size - size;
        if (sizeDiff == 0u)
        {
            foundIt->isFree = false;
            return foundIt->data;
        }

        if (sizeDiff > 0u)
        {
            union
            {
                void* asVoidPtr;
                std::byte* asBytePtr;
            };

            asVoidPtr = foundIt->data;
            void* newEntryData = asBytePtr + size;

            m_FreeList.push_back({ sizeDiff, newEntryData, true });
            foundIt->size -= size;
            foundIt->isFree = false;
            return foundIt->data;
        }
    }

    return nullptr;
}

void FreeListAllocator::Free(void* data)
{
    auto foundIt = std::find_if(m_FreeList.begin(), m_FreeList.end(),
        [data](const ListEntry& entry)
    {
        return entry.data == data;
    }
    );

    if (foundIt == m_FreeList.end())
    {
        assert(false && "Tried to free data that is not in allocated pool");
        return;
    }

    foundIt->isFree = true;

    auto eraseFromIt = m_FreeList.end();
    auto eraseToIt = m_FreeList.end();

    // merge with next element
    auto nextElementIt = std::next(foundIt);
    if (nextElementIt != m_FreeList.end())
    {
        if (nextElementIt->isFree)
        {
            if (MergeEntries(*foundIt, *nextElementIt))
            {
                eraseFromIt = nextElementIt;
                eraseToIt = nextElementIt;
            }
        }
    }

    // merge with previous element
    if (foundIt != m_FreeList.begin())
    {
        auto previousElementIt = std::prev(foundIt);
        if (previousElementIt->isFree)
        {
            if (MergeEntries(*previousElementIt, *foundIt))
            {
                eraseFromIt = foundIt;
                if (eraseToIt == m_FreeList.end())
                {
                    eraseToIt = foundIt;
                }
            }
        }
    }

    m_FreeList.erase(eraseFromIt, eraseToIt);
}

void FreeListAllocator::Clear()
{

}

bool FreeListAllocator::MergeEntries(ListEntry& mergeTo, ListEntry& mergeFrom)
{
    union
    {
        void* asVoidPtr;
        std::byte* asBytePtr;
    };

    asVoidPtr = mergeTo.data;

    void* nextMemoryBlock = (asBytePtr + mergeTo.size);

    if (nextMemoryBlock == mergeFrom.data)
    {
        mergeTo.size += mergeFrom.size;
        mergeFrom.size = 0u;

        return true;
    }

    return false;
}
