#pragma once

#include <SFML/System/Vector2.hpp>

class ExplosiveComponent
{
public:
    ExplosiveComponent(int power, const sf::Vector2i& tilePosition);

    void SpawnExplosion();

private:
    int myPower = 1;
    sf::Vector2i myTilePosition = {0, 0};
};