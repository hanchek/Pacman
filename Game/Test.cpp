#include "Game\pch.h"
#include "Test.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/ControlsComponent.h"
#include "Components/MovementComponent.h"
#include "Components/RenderComponent.h"
#include "Components/StaticWallComponent.h"

#include "CollisionSystem/CollisionManager.h"
#include "EntityComponentSystem/EntityComponentManager.h"
#include "ResourceManager/ResourceManager.h"

static EntityID playerEntity;

void Test::CreateBackGround()
{
    auto componentManager = EntityComponentManager::GetInstance();

    const EntityID backGroundID = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(backGroundID, "worldBackground");
}

void Test::CreatePlayer()
{
    auto componentManager = EntityComponentManager::GetInstance();

    playerEntity = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(playerEntity, "player");
    renderComponent.SetPosition({ 150.f, 150.f });
    renderComponent.SetSize({ 100.f, 100.f });
    componentManager->CreateComponent<MovementComponent>(playerEntity, 200.f);
    componentManager->CreateComponent<ControlsComponent>(playerEntity);
}

void Test::DestroyPlayer()
{
    EntityComponentManager::GetInstance()->DestroyEntity(playerEntity);
}

void Test::CreateWalls()
{
    int tiles[MAP_WIDTH][MAP_HEIGHT] = {
        {1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1}
    };

    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            if (tiles[i][j])
            {
                CreateWall({i,j});
            }
        }
    }

    CollisionManager::GetInstance()->UpdateTiles();
}

void Test::CreateWall(const sf::Vector2i& tile)
{
    auto componentManager = EntityComponentManager::GetInstance();

    const EntityID wallEntity = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(wallEntity, "concrete_wall");
    renderComponent.SetPosition(Utils::GetTilePosition(tile));
    renderComponent.SetSize({ MAP_SCALE, MAP_SCALE });
    StaticWallComponent& wallComponent = componentManager->CreateComponent<StaticWallComponent>(wallEntity);
    wallComponent.Init(renderComponent);
}

void Test::DrawMissingTexture(sf::RenderWindow& window)
{
    window.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("62")));
}
