#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t size, void* data)
{
    m_Data = data;
    m_DataSize = size;
    m_IsMemoryOwner = false;
}

LinearAllocator::LinearAllocator(size_t size)
{
    m_Data = operator new(size);
    m_DataSize = size;
    m_IsMemoryOwner = true;
}
LinearAllocator::~LinearAllocator()
{
    if (m_IsMemoryOwner)
    {
        delete m_Data;
    }
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
