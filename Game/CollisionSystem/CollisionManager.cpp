#include "Game/pch.h"
#include "CollisionManager.h"

#include "Game/EntityComponentSystem/EntityComponentManager.h"
#include "Game/Components/StaticWallComponent.h"

bool CollisionManager::IsTilePassable(const sf::Vector2i& tile)
{
    return IsTile(tile) && !myTiles[tile.x][tile.y];
}

bool CollisionManager::IsTile(const sf::Vector2i& tile)
{
    return (tile.x >= 0) && (tile.x < MAP_WIDTH) && (tile.y >= 0) && (tile.y < MAP_HEIGHT);
}

void CollisionManager::UpdateTiles()
{
    ResetTiles();

    EntityComponentManager::GetInstance()->ForEachComponent<StaticWallComponent>([this](StaticWallComponent& component) {
        const sf::Vector2i tile = component.GetTile();
        if (IsTile(tile))
        {
            myTiles[tile.x][tile.y] = 1;
        }
        else
        {
            assert("Wall component is out of tile map");
        }
    });
}

CollisionManager::CollisionManager()
{
    ResetTiles();
}

void CollisionManager::ResetTiles()
{
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            myTiles[i][j] = 0;
        }
    }
}
