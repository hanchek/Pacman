#pragma once

class IAllocator
{
public:
    virtual ~IAllocator() = default;

    virtual void* Allocate(size_t size) = 0;
    virtual void Free(void* data) = 0;
    virtual void Clear() = 0;
};