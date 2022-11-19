#include "Game/pch.h"
#include "Test.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Engine/Animation/ColorAnimation.h"
#include "Engine/Animation/SpriteAnimation.h"
#include "Engine/Components/AnimationPlayerComponent.h"
#include "Engine/Components/EntityDestroyerComponent.h"
#include "Engine/Components/RenderComponent.h"
#include "Engine/EntityComponentSystem/EntityComponentManager.h"
#include "Engine/ResourceManager/ResourceManager.h"
#include "Game/CollisionSystem/CollisionManager.h"
#include "Game/Components/ControlsComponent.h"
#include "Game/Components/ExplosiveComponent.h"
#include "Game/Components/MovementComponent.h"
#include "Game/Components/StaticWallComponent.h"

static EntityID playerEntity;

void Test::CreateAnimations()
{
    auto resourceManager = ResourceManager::GetInstance();

    std::vector<sf::Vector2i> frames;
    std::unique_ptr<SpriteAnimation> spriteAnimation;
    std::unique_ptr<ColorAnimation> colorAnimation;

    frames = { {0,0}, {0,0}, {0,0}, {16,0}, {0,0}, {16,0} };
    spriteAnimation = std::make_unique<SpriteAnimation>(std::move(frames));
    spriteAnimation->SetName("bomb_animation");
    resourceManager->AddAnimation(std::move(spriteAnimation));

    frames = { {0,0}, { 48,0}, {96,0}, {144,0}, {192,0}, {240,0}, {288,0} };
    spriteAnimation = std::make_unique<SpriteAnimation>(std::move(frames));
    spriteAnimation->SetName("explosion");
    resourceManager->AddAnimation(std::move(spriteAnimation));

    colorAnimation = std::make_unique<ColorAnimation>(sf::Color::White, sf::Color(255, 255, 255, 0));
    colorAnimation->SetName("explosion_fade");
    resourceManager->AddAnimation(std::move(colorAnimation));

    frames = { {0,0}, {16,0}, {32,0}, {48,0} };
    spriteAnimation = std::make_unique<SpriteAnimation>(std::move(frames));
    spriteAnimation->SetName("bottom_movement");
    resourceManager->AddAnimation(std::move(spriteAnimation));

    frames = { {0,24}, {16,24}, {32,24}, {48,24} };
    spriteAnimation = std::make_unique<SpriteAnimation>(std::move(frames));
    spriteAnimation->SetName("right_movement");
    resourceManager->AddAnimation(std::move(spriteAnimation));
        
    frames = { {0,48}, {16,48}, {32,48}, {48,48} };
    spriteAnimation = std::make_unique<SpriteAnimation>(std::move(frames));
    spriteAnimation->SetName("left_movement");
    resourceManager->AddAnimation(std::move(spriteAnimation));

    frames = { {0,72}, {16,72}, {32,72}, {48,72} };
    spriteAnimation = std::make_unique<SpriteAnimation>(std::move(frames));
    spriteAnimation->SetName("top_movement");
    resourceManager->AddAnimation(std::move(spriteAnimation));
}

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
    componentManager->CreateComponent<AnimationPlayerComponent>(
        playerEntity, 1.f, "bottom_movement").Pause();
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

    ExplosiveComponent& explosiveComponent = componentManager->CreateComponent<ExplosiveComponent>(
        bombEntity, 1, Utils::GetNearestTile(renderComponent.GetPosition()));

    EntityDestroyerComponent& entityDestroyerComponent = componentManager->CreateComponent<EntityDestroyerComponent>(
        bombEntity, bombEntity);

    AnimationPlayerComponent& animationPlayer = componentManager->CreateComponent<AnimationPlayerComponent>(
        bombEntity, 5.f, "bomb_animation");
    animationPlayer.SetIsRepeatable(false);
    animationPlayer.onAnimationEnd.connect<&ExplosiveComponent::SpawnExplosion>(explosiveComponent);
    animationPlayer.onAnimationEnd.connect<&EntityDestroyerComponent::DestroyEntity>(entityDestroyerComponent);
}

void Test::DrawMissingTexture(sf::RenderWindow& window)
{
    window.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("62")));
}
