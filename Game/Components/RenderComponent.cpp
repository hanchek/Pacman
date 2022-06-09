#include "RenderComponent.h"

#include "Game/ResourceManager/ResourceManager.h"

RenderComponent::RenderComponent(const std::string& textureName)
{
    mySprite.setTexture(ResourceManager::GetInstance()->GetTexture(textureName));
}

void RenderComponent::Draw(sf::RenderWindow& window) const
{
    window.draw(mySprite);
}

void RenderComponent::SetSize(const sf::Vector2f& size)
{
    const sf::Texture* texture = mySprite.getTexture();
    if (texture)
    {
        const sf::Vector2u& textureSize = texture->getSize();
        mySprite.setScale(size.x / textureSize.x, size.y / textureSize.y);
    }
}

sf::Vector2f RenderComponent::GetSize() const
{
    const sf::Texture* texture = mySprite.getTexture();
    if (texture)
    {
        const sf::Vector2u& textureSize = texture->getSize();
        const sf::Vector2f& scale = mySprite.getScale();
        return { textureSize.x * scale.x, textureSize.y * scale.y };
    }

    return {0.f, 0.f};
}

void RenderComponent::SetPosition(const sf::Vector2f& position)
{
    mySprite.setPosition(position);
}

sf::Vector2f RenderComponent::GetPosition() const
{
    return mySprite.getPosition();
}

void RenderComponent::MovePosition(const sf::Vector2f& distance)
{
    mySprite.move(distance);
}
