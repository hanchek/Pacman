#pragma once

#include <vector>

#include "json.hpp"

#include "Serialization/TypeTraits.h"

class JSONSerializer
{
public:
    virtual ~JSONSerializer() = default;

    void LoadFromFile(const std::string& filename);
    void SaveToFile(const std::string& filename) const;
    std::string GetDump() const { return myJson.dump(); }

    bool Read(const std::string& key, int& value) const;
    bool Read(const std::string& key, float& value) const;
    bool Read(const std::string& key, std::string& value) const;

    bool Write(const std::string& key, int value);
    bool Write(const std::string& key, float value);
    bool Write(const std::string& key, const std::string& value);

    template<class T>
    bool Write(const std::string& key, const std::vector<T>& value)
    {
        MoveTop(key);
        GetTop() = nlohmann::json::array();
        for (int i = 0; i < value.size(); ++i)
        {
            GetTop()[i] = value[i];
        }
        PopTop();
        return true;
    }

    template<class T>
    bool Read(const std::string& key, std::vector<T>& value) const
    {
        if (GetTop().contains(key) && GetTop()[key].is_array())
        {
            value = GetTop()[key].get<std::vector<T>>();
        }

        return false;
    }

    nlohmann::json& GetTop() { return myStack.empty() ? myJson : *myStack.back(); }
    const nlohmann::json& GetTop() const { return myStack.empty() ? myJson : *myStack.back(); }

    nlohmann::json& GetTop(const std::string& key) { return GetTop()[key]; }
    const nlohmann::json& GetTop(const std::string& key) const { return GetTop()[key]; }

protected:
    void MoveTop(const std::string& key);
    void PopTop();

    nlohmann::json myJson;
    std::vector<nlohmann::json*> myStack;
};

class JSONWriter : public JSONSerializer
{
public:
    template<class T>
    bool Process(const std::string& key, T& value)
    {
        if constexpr (IsWriteable<T&>::value)
        {
            return Write(key, value);
        }
        else
        {
            MoveTop(key);
            const bool result = value.Process(*this);
            PopTop();
            return result;
        }
    }
};

class JSONReader : public JSONSerializer
{
public:
    template<class T>
    bool Process(const std::string& key, T& value)
    {
        if constexpr (IsReadable<T&>::value)
        {
            return Read(key, value);
        }
        else
        {
            MoveTop(key);
            const bool result = value.Process(*this);
            PopTop();
            return result;
        }
    }
};
