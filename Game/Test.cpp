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

void Test::CreateBackGround()
{
    auto componentManager = EntityComponentManager::GetInstance();

    const EntityID backGroundID = componentManager->CreateEntity();
    RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(backGroundID, "worldBackground");
    renderComponent.SetSize({ MAP_WIDTH * MAP_SCALE, MAP_HEIGHT * MAP_SCALE });
    renderComponent.SetPosition({ MAP_WIDTH * MAP_SCALE / 2.f, MAP_HEIGHT * MAP_SCALE / 2.f });
    renderComponent.SetRenderOrder(-1);
}

void Test::DrawMissingTexture(sf::RenderWindow& window)
{
    window.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("62")));
}
