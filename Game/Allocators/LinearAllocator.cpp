#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t size, void* data)
{
    m_Data = static_cast<std::byte*>(data);
    m_DataSize = size;
}

void* LinearAllocator::Allocate(size_t size)
{
    if (m_DataSize - m_AllocatedSize < size)
    {
        return nullptr;
    }

    union
    {
        void* asVoidPtr;
        std::byte* asBytePtr;
    };

    asVoidPtr = m_Data;
    asBytePtr += m_AllocatedSize;

    m_AllocatedSize += size;

    return asVoidPtr;
}

void LinearAllocator::Clear()
{
    m_AllocatedSize = 0;
}
