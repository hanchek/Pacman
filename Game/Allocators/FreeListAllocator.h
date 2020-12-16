#pragma once

#include <vector>

class FreeListAllocator
{
public:
    FreeListAllocator(size_t size, void* data);

    void* Allocate(size_t size);
    void Free(void* data);
    void Clear();
private:

    struct ListEntry
    {
        size_t size;
        void* data;
        bool isFree;
    };

    static bool MergeEntries(ListEntry& mergeTo, ListEntry& mergeFrom);

    std::vector<ListEntry> m_FreeList;
};