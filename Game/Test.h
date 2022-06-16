#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf
{
    class RenderWindow;
}

namespace Test
{
    void CreateBackGround();
    void CreatePlayer();
    void CreateAnimatedPlayer();
    void DestroyPlayer();

    void CreateWalls();
    void CreateWall(const sf::Vector2i& tile);

    void DrawMissingTexture(sf::RenderWindow& window);
}
