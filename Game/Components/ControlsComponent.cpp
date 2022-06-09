#include "Game/pch.h"
#include "ControlsComponent.h"

#include "MovementComponent.h"

void ControlsComponent::Update(MovementComponent& movementComponent)
{
    myMovementDirection = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { myMovementDirection = { -1.f, 0.f }; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { myMovementDirection = { 0.f, -1.f }; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { myMovementDirection = { 1.f, 0.f }; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { myMovementDirection = { 0.f, 1.f }; }

    movementComponent.SetVelocity(myMovementDirection);
}
