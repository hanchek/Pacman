#pragma once

#include <SFML/System/Vector2.hpp>

class MovementComponent;

class ControlsComponent
{
public:
    void Update(MovementComponent& movementComponent);

private:
    sf::Vector2i myMovementDirection = { 0, 0 };
};