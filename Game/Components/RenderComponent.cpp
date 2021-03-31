#include "RenderComponent.h"

#include "Game/Render/RenderManager.h"
#include "Game/ResourceManager/ResourceManager.h"

RenderComponent::RenderComponent(const std::string& textureName)
{
    if (RenderManager* renderManager = RenderManager::GetInstance())
    {
        renderManager->RegisterRenderComponent(this);
    }
    if (ResourceManager* resourceManager = ResourceManager::GetInstance())
    {
        m_Sprite.setTexture(resourceManager->GetTexture(textureName));
    }
}

RenderComponent::~RenderComponent()
{
    if (RenderManager* renderManager = RenderManager::GetInstance())
    {
        renderManager->UnregisterRenderComponent(this);
    }
}

void RenderComponent::Draw(sf::RenderWindow& window) const
{
    window.draw(m_Sprite);
}

void RenderComponent::SetSize(const sf::Vector2f& size)
{
    const sf::Texture* texture = m_Sprite.getTexture();
    if (texture)
    {
        const sf::Vector2u textureSize = texture->getSize();
        m_Sprite.setScale(size.x / textureSize.x, size.y / textureSize.y);
    }
    
}

sf::Vector2f RenderComponent::GetSize() const
{
    const sf::Texture* texture = m_Sprite.getTexture();
    if (texture)
    {
        const sf::Vector2u textureSize = texture->getSize();
        const sf::Vector2f scale = m_Sprite.getScale();
        return sf::Vector2f(textureSize.x * scale.x, textureSize.y * scale.y);
    }
}
