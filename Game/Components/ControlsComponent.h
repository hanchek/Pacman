#pragma once

#include <SFML/System/Vector2.hpp>

#include "Engine/Utils/Utils.h"

class AnimationPlayerComponent;
class MovementComponent;

class ControlsComponent
{
public:
    void Update(MovementComponent& movementComponent, AnimationPlayerComponent& animationPlayer);

private:
    void SwitchAnimation(AnimationPlayerComponent& animationPlayer, Utils::Orientation newOrientation);

    sf::Vector2i myMovementDirection = { 0, 0 };
    Utils::Orientation myOrientation = Utils::Orientation::None;
};