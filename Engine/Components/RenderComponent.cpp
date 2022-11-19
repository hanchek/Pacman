#include "pch.h"
#include "RenderComponent.h"

#include "ResourceManager/ResourceManager.h"

RenderComponent::RenderComponent(const std::string& textureName)
{
    mySprite.setTexture(ResourceManager::GetInstance()->GetTexture(textureName));
    const sf::IntRect& textureRect = mySprite.getTextureRect();
    mySprite.setOrigin(textureRect.width / 2.f, textureRect.height / 2.f);
}

RenderComponent::RenderComponent(const std::string& textureName, const sf::IntRect& textureRect)
{
    mySprite.setTexture(ResourceManager::GetInstance()->GetTexture(textureName));
    mySprite.setTextureRect(textureRect);
    mySprite.setOrigin(textureRect.width / 2.f, textureRect.height / 2.f);
}

void RenderComponent::Draw(sf::RenderWindow& window) const
{
    window.draw(mySprite);
}

void RenderComponent::SetSize(const sf::Vector2f& size)
{
    const sf::IntRect& textureRect = mySprite.getTextureRect();
    mySprite.setScale(size.x / textureRect.width, size.y / textureRect.height);
}

sf::Vector2f RenderComponent::GetSize() const
{
    const sf::IntRect& textureRect = mySprite.getTextureRect();
    const sf::Vector2f& scale = mySprite.getScale();
    return { textureRect.width * scale.x, textureRect.height * scale.y };
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

void RenderComponent::SetTextureRectPosition(const sf::Vector2i& position)
{
    sf::IntRect textureRect = mySprite.getTextureRect();
    textureRect.left = position.x;
    textureRect.top = position.y;
    mySprite.setTextureRect(textureRect);
}

sf::Vector2i RenderComponent::GetTextureRectPosition() const
{
    const sf::IntRect& textureRect = mySprite.getTextureRect();
    return { textureRect.left, textureRect.top };
}
