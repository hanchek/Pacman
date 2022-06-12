#include "Game/pch.h"
#include "ControlsComponent.h"

#include "MovementComponent.h"

void ControlsComponent::Update(MovementComponent& movementComponent)
{
    myMovementDirection = { 0, 0 };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { myMovementDirection.x -= 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { myMovementDirection.y -= 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { myMovementDirection.x += 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { myMovementDirection.y += 1; }

    movementComponent.SetDirection(myMovementDirection);
}
