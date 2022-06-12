#pragma once

class RenderComponent;

#include <SFML/System/Vector2.hpp>

class StaticWallComponent
{
public:
    void Init(RenderComponent& renderComponent);

    sf::Vector2i GetTile() const { return myTile; }

private:
    sf::Vector2i myTile = { -1, -1 };
};
