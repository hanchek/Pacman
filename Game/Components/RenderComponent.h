#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Game/EntityComponentSystem/Component.h"

class RenderComponent : public Component
{
public:
    RenderComponent(const std::string& textureName);
    ~RenderComponent();

    void Draw(sf::RenderWindow& window) const;

    void SetSize(const sf::Vector2f& size);
    sf::Vector2f GetSize() const;

    void SetPosition(const sf::Vector2f& position);
    sf::Vector2f GetPosition() const;
    void MovePosition(const sf::Vector2f& distance);

    DEFINE_COMPONENT_NAME(RenderComponent);

private:
    sf::Sprite m_Sprite;
};