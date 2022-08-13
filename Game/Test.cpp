#include "Game\pch.h"
#include "Test.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/AnimationComponent.h"
#include "Components/ControlsComponent.h"
#include "Components/MovementAnimationComponent.h"
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
    renderComponent.SetSize({ MAP_WIDTH * MAP_SCALE, MAP_HEIGHT * MAP_SCALE });
    renderComponent.SetPosition({ MAP_WIDTH * MAP_SCALE / 2.f, MAP_HEIGHT * MAP_SCALE / 2.f });
    renderComponent.SetRenderOrder(-1);
}

void Test::CreatePlayer()
{
    auto componentManager = EntityComponentManager::GetInstance();

    playerEntity = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(
        playerEntity, "player_animated", sf::IntRect(0, 0, 15, 24));
    renderComponent.SetPosition({ 150.f, 150.f });
    renderComponent.SetSize({ 62.5f, 100.f });
    componentManager->CreateComponent<MovementComponent>(playerEntity, 200.f);
    componentManager->CreateComponent<ControlsComponent>(playerEntity);
}

void Test::CreateAnimatedPlayer()
{
    auto componentManager = EntityComponentManager::GetInstance();

    playerEntity = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(
        playerEntity, "player_animated", sf::IntRect(0, 0, 16, 24));
    renderComponent.SetPosition({ 150.f, 150.f });
    renderComponent.SetSize({ 62.5f, 100.f });
    componentManager->CreateComponent<MovementComponent>(playerEntity, 300.f);
    componentManager->CreateComponent<ControlsComponent>(playerEntity);
    MovementAnimationFrames animationFrames;
    animationFrames.bottomFrames = { {0,0}, {16,0}, {32,0}, {48,0} };
    animationFrames.rightFrames = { {0,24}, {16,24}, {32,24}, {48,24} };
    animationFrames.leftFrames = { {0,48}, {16,48}, {32,48}, {48,48} };
    animationFrames.topFrames = { {0,72}, {16,72}, {32,72}, {48,72} };
    componentManager->CreateComponent<MovementAnimationComponent>(playerEntity, std::move(animationFrames), 1.f);
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

void Test::CreateBomb()
{
    auto componentManager = EntityComponentManager::GetInstance();

    const EntityID bombEntity = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(
        bombEntity, "bomb_animated", sf::IntRect(0, 0, 16, 20));
    renderComponent.SetPosition({ 350.f, 350.f });
    renderComponent.SetSize({ 80.f, 100.f });
    std::vector<sf::Vector2i> animationFrames = { {0,0}, {0,0}, {0,0}, {16,0}, {0,0}, {16,0} };
    AnimationComponent& animationComponent = componentManager->CreateComponent<AnimationComponent>(
        bombEntity, std::move(animationFrames), 5.f);
    animationComponent.SetIsRepeatable(false);
}

void Test::DrawMissingTexture(sf::RenderWindow& window)
{
    window.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("62")));
}
