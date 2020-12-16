#pragma once
#include <cstddef>

class LinearAllocator
{
public:
    LinearAllocator(size_t size, void* data);

    void* Allocate(size_t size);
    void Clear();

private:

    void* m_Data = nullptr;
    size_t m_DataSize = 0;
    size_t m_AllocatedSize = 0;
};