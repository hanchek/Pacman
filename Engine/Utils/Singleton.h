#pragma once

#include <memory>

template<class T>
class Singleton
{
public:
    static T* GetInstance()
    {
        return ms_Instance;
    }

    static void CreateInstance()
    {
        if (!ms_Instance)
        {
            ms_Instance = new T();
        }
    }

    static void DestroyInstance()
    {
        if (ms_Instance)
        {
            delete ms_Instance;
            ms_Instance = nullptr;
        }
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    inline static T* ms_Instance = nullptr;
};
