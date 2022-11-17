#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class RenderComponent
{
public:
    RenderComponent(const std::string& textureName);
    RenderComponent(const std::string& textureName, const sf::IntRect& textureRect);

    void Draw(sf::RenderWindow& window) const;

    void SetSize(const sf::Vector2f& size);
    sf::Vector2f GetSize() const;

    void SetPosition(const sf::Vector2f& position);
    sf::Vector2f GetPosition() const;

    void MovePosition(const sf::Vector2f& distance);

    void SetTextureRectPosition(const sf::Vector2i& position);
    sf::Vector2i GetTextureRectPosition() const;

    void SetRenderOrder(int order) { myRenderOrder = order; }
    int GetRenderOrder() const { return myRenderOrder; }

private:
    sf::Sprite mySprite;
    int myRenderOrder = 0;
};