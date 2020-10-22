#include "ResourceManager.h"
#include <filesystem>
#include <cassert>

std::unordered_map<size_t, std::unique_ptr<sf::Texture>> ResourceManager::s_Textures;

const sf::Texture& ResourceManager::GetTexture(const std::string& name)
{
    const std::size_t nameHash = std::hash<std::string>{}(name);
    auto it = s_Textures.find(nameHash);

    if (it != s_Textures.end())
    {
        return *(it->second);
    }

    // if search failed fill texture with red color

    sf::Image errorImage;
    errorImage.create(128u, 128u, sf::Color::Red);
    TexturePtr errorTexture = std::make_unique<sf::Texture>();
    errorTexture->loadFromImage(errorImage);

    // insert returns a pair consisting of an iterator to the inserted element
    // and a bool denoting whether the insertion took place
    const auto insertResult = s_Textures.insert(std::make_pair(nameHash, std::move(errorTexture)));
    const auto insertedElement = insertResult.first;

    return *(insertedElement->second);
}

void ResourceManager::PreloadTexturesFromFolder(const std::string& relativePath)
{
    std::filesystem::path fullPath = std::filesystem::current_path();
    // append relative path to current path
    fullPath /= std::filesystem::path(relativePath);

    // iterate through all entries in 
    for (const auto& dirEntry : std::filesystem::directory_iterator(fullPath))
    {
        if (dirEntry.is_regular_file())
        {
            const std::string entryString = dirEntry.path().string();
            TexturePtr texture = std::make_unique<sf::Texture>();
            if (texture->loadFromFile(entryString))
            {
                const size_t offset1 = entryString.find_last_of("/\\");
                const size_t offset2 = entryString.find_last_of('.');
                const std::string fileName = entryString.substr(offset1 + 1, offset2 - offset1 - 1);

                const size_t nameHash = std::hash<std::string>{}(fileName);
                s_Textures.insert(std::make_pair(nameHash, std::move(texture)));
            }
            else
            {
                assert(false && "Didn't manage to load texture");
            }
        }
    }
}

void ResourceManager::ReleaseResources()
{
    s_Textures.clear();
}
