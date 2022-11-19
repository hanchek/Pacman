#include "Game/pch.h"
#include "ExplosionSystem.h"

#include "Game/CollisionSystem/CollisionManager.h"
#include "Game/Components/AnimationPlayerComponent.h"
#include "Game/Components/EntityDestroyerComponent.h"
#include "Game/Components/RenderComponent.h"
#include "Game/EntityComponentSystem/EntityComponentManager.h"

namespace ExplosionSystem
{
    std::vector<sf::Vector2i> GetImpactedTiles(int power, const sf::Vector2i& tilePosition)
    {
        std::vector<sf::Vector2i> result;
        auto collisionManager = CollisionManager::GetInstance();

        result.push_back(tilePosition);

        // check all tiles on the right
        for (int i = 1; i <= power; ++i)
        {
            sf::Vector2i nextTile = { tilePosition.x + i, tilePosition.y };
            if (collisionManager->IsTilePassable(nextTile))
            {
                result.push_back(nextTile);
            }
            else
            {
                break;
            }
        }

        // check all tiles on the left
        for (int i = 1; i <= power; ++i)
        {
            sf::Vector2i nextTile = { tilePosition.x - i, tilePosition.y };
            if (collisionManager->IsTilePassable(nextTile))
            {
                result.push_back(nextTile);
            }
            else
            {
                break;
            }
        }

        // check all tiles from above
        for (int i = 1; i <= power; ++i)
        {
            sf::Vector2i nextTile = { tilePosition.x, tilePosition.y - i };
            if (collisionManager->IsTilePassable(nextTile))
            {
                result.push_back(nextTile);
            }
            else
            {
                break;
            }
        }

        // check all tiles from below
        for (int i = 1; i <= power; ++i)
        {
            sf::Vector2i nextTile = { tilePosition.x, tilePosition.y + i };
            if (collisionManager->IsTilePassable(nextTile))
            {
                result.push_back(nextTile);
            }
            else
            {
                break;
            }
        }

        return result;
    }

    void SpawnExplosion(int power, const sf::Vector2i& tilePosition)
    {
        auto ecs = EntityComponentManager::GetInstance();

        const std::vector<sf::Vector2i> impactedTiles = GetImpactedTiles(power, tilePosition);
        for (const sf::Vector2i& impactedTile : impactedTiles)
        {
            const EntityID explosionEntity = ecs->CreateEntity();

            RenderComponent& renderComponent = ecs->CreateComponent<RenderComponent>(
                explosionEntity, "explosion", sf::IntRect(0, 0, 48, 48));
            renderComponent.SetPosition(Utils::GetTilePosition(impactedTile));
            renderComponent.SetSize({ MAP_SCALE, MAP_SCALE });

            EntityDestroyerComponent& destroyerComponent = ecs->CreateComponent<EntityDestroyerComponent>(
                explosionEntity, explosionEntity);

            const float duration = 0.5;

            AnimationPlayerComponent& animationPlayer = ecs->CreateComponent<AnimationPlayerComponent>(
                explosionEntity, duration, "explosion");
            animationPlayer.SetIsRepeatable(false);
            animationPlayer.onAnimationEnd.connect<&EntityDestroyerComponent::DestroyEntity>(destroyerComponent);

            // TODO perform damage calculation
        }
    }
}

