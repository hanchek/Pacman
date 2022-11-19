#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>

#include "Game/Animation/Animation.h"
#include "Game/Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
    friend Singleton<ResourceManager>;
    using AnimationPtr = std::unique_ptr<Animation>;

    const sf::Texture& GetTexture(const std::string& name);
    void PreloadTexturesFromFolder(const std::string& relativePath);

    const Animation* GetAnimation(const std::string& name) const;
    void AddAnimation(AnimationPtr&& animation);
    
private:
    //TODO check if it is really necessary to use dynamic memory allocation here
    using TexturePtr = std::unique_ptr<sf::Texture>;
    

    ResourceManager() = default;
    ~ResourceManager() = default;
    std::unordered_map<size_t, TexturePtr> theTextures;
    std::unordered_map<size_t, AnimationPtr> theAnimations;
};