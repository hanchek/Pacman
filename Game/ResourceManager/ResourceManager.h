#pragma once
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "Game/Singleton.h"


class ResourceManager : public Singleton<ResourceManager>
{
public:
    friend Singleton<ResourceManager>;

    typedef std::unique_ptr<sf::Texture> TexturePtr;

    const sf::Texture& GetTexture(const std::string& name);
    void PreloadTexturesFromFolder(const std::string& relativePath);
private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    std::unordered_map<size_t, TexturePtr> s_Textures;
};