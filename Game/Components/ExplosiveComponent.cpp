#include "Game/pch.h"
#include "ExplosiveComponent.h"

#include "Game/ExplosionSystem/ExplosionSystem.h"

ExplosiveComponent::ExplosiveComponent(int power, const sf::Vector2i& tilePosition)
    : myPower(power),
    myTilePosition(tilePosition)
{
}

void ExplosiveComponent::SpawnExplosion()
{
    ExplosionSystem::SpawnExplosion(myPower, myTilePosition);
}