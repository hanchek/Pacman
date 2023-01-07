#include "pch.h"
#include "Serializer.h"

void JSONSerializer::LoadFromFile(const std::string& filename)
{
    std::ifstream inputStream(filename);

    inputStream >> myJson;
}

void JSONSerializer::SaveToFile(const std::string& filename) const
{
    std::ofstream outputStream(filename);
    outputStream << std::setw(2) << myJson << std::endl;
}

bool JSONSerializer::Read(const std::string& key, int& value) const
{
    if (GetTop().contains(key) && GetTop()[key].is_number_integer())
    {
        value = GetTop()[key];
        return true;
    }

    return false;
}

bool JSONSerializer::Read(const std::string& key, float& value) const
{
    if (GetTop().contains(key) && GetTop()[key].is_number_float())
    {
        value = GetTop()[key];
        return true;
    }

    return false;
}

bool JSONSerializer::Read(const std::string& key, std::string& value) const
{
    if (GetTop().contains(key) && GetTop()[key].is_string())
    {
        value = GetTop()[key];
        return true;
    }

    return false;
}

bool JSONSerializer::Write(const std::string& key, int value)
{
    GetTop()[key] = value;
    return true;
}

bool JSONSerializer::Write(const std::string& key, float value)
{
    GetTop()[key] = value;
    return true;
}

bool JSONSerializer::Write(const std::string& key, const std::string& value)
{
    GetTop()[key] = value;
    return true;
}

void JSONSerializer::MoveTop(const std::string& key)
{
    myStack.push_back(&GetTop(key));
}

void JSONSerializer::PopTop()
{
    myStack.pop_back();
}
