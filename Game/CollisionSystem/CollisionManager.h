#pragma once

#include "Engine/Utils/Singleton.h"
#include "Engine/Utils/Constants.h"

class CollisionManager : public Singleton<CollisionManager>
{
public:
    friend Singleton<CollisionManager>;

    bool IsTilePassable(const sf::Vector2i& tile);
    // return true if tile fits in MAP_WIDTH, MAP_HEIGHT
    bool IsTile(const sf::Vector2i& tile);

    void UpdateTiles();

private:
    CollisionManager();
    ~CollisionManager() = default;

    void ResetTiles();

    int myTiles[MAP_WIDTH][MAP_HEIGHT];
};