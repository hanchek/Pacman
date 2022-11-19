#include "Game/pch.h"
#include "MovementComponent.h"

#include "Engine/Components/RenderComponent.h"
#include "Game/CollisionSystem/CollisionManager.h"

MovementComponent::MovementComponent(float speed) : mySpeed(speed)
{
}

void MovementComponent::Update(float dt, RenderComponent& renderComponent)
{
    if (myDirection == sf::Vector2i(0, 0))
    {
        return;
    }

    const sf::Vector2f currentPosition = renderComponent.GetPosition();
    const sf::Vector2i currentTile = Utils::GetNearestTile(currentPosition);
    const sf::Vector2f currentTilePosition = Utils::GetTilePosition(currentTile);
    const sf::Vector2f shift =  currentPosition - currentTilePosition;

    sf::Vector2i wantedTile = currentTile;

    if (shift.x > EPS)
    {
        if (myDirection.x > 0) { ++wantedTile.x; }
    }
    else if(shift.x < -EPS)
    {
        if (myDirection.x < 0) { --wantedTile.x; }
    }
    else
    {
        wantedTile.x += myDirection.x;
    }

    if (shift.y > EPS)
    {
        if (myDirection.y > 0) { ++wantedTile.y; }
    }
    else if (shift.y < -EPS)
    {
        if (myDirection.y < 0) { --wantedTile.y; }
    }
    else
    {
        wantedTile.y += myDirection.y;
    }

    // check for the walls
    {
        auto collisionManager = CollisionManager::GetInstance();

        if (!collisionManager->IsTilePassable(wantedTile))
        {
            return;
        }
    }

    // TODO consider if this clamp is needed
    // prevents from leaving map borders
    Utils::ClampVector(wantedTile, sf::Vector2i( 0, 0 ), sf::Vector2i( MAP_WIDTH, MAP_HEIGHT ));

    const sf::Vector2f wantedPosition = Utils::GetTilePosition(wantedTile);

    float distanceToMove = mySpeed * dt;
    sf::Vector2f difference = wantedPosition - currentPosition;
    sf::Vector2f moveResult = { 0.f, 0.f };

    // to support cornering we want to decrease difference of the coordinate that is lesser
    if (fabs(difference.x) < fabs(difference.y))
    {
        if (fabs(difference.x) < CORNERING)
        {
            // moving horizontally
            moveResult.x = Utils::ReduceAbs(difference.x, distanceToMove);
            distanceToMove -= fabs(moveResult.x);
            // moving vertically
            moveResult.y = Utils::ReduceAbs(difference.y, distanceToMove);
        }
    }
    else
    {
        if(fabs(difference.y) < CORNERING)
        {
            // moving vertically
            moveResult.y = Utils::ReduceAbs(difference.y, distanceToMove);
            distanceToMove -= fabs(moveResult.y);
            // moving horizontally
            moveResult.x = Utils::ReduceAbs(difference.x, distanceToMove);
        }
    }

    renderComponent.MovePosition(moveResult);
}
