#pragma once
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <memory>


class ResourceManager
{
public:
    typedef std::unique_ptr<sf::Texture> TexturePtr;
    static const sf::Texture& GetTexture(const std::string& name);
    static void PreloadTexturesFromFolder(const std::string& relativePath);

    static void ReleaseResources();
private:
    static std::unordered_map<size_t, TexturePtr> s_Textures;
};