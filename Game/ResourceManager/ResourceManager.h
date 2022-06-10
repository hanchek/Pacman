#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>

#include "Game/Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
    friend Singleton<ResourceManager>;

    const sf::Texture& GetTexture(const std::string& name);
    void PreloadTexturesFromFolder(const std::string& relativePath);
private:
    //TODO check if it is really necessary to use dynamic memory allocation here
    using TexturePtr = std::unique_ptr<sf::Texture>;

    ResourceManager() = default;
    ~ResourceManager() = default;
    std::unordered_map<size_t, TexturePtr> theTextures;
};