#pragma once

#include <SFML/Graphics.hpp>

class MovementComponent;

class ControlsComponent
{
public:
    void Update(MovementComponent& movementComponent);

private:
    sf::Vector2f myMovementDirection = {0.f, 0.f};
};