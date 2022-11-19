#include "Game/pch.h"
#include "ControlsComponent.h"

#include "MovementComponent.h"
#include "AnimationPlayerComponent.h"

void ControlsComponent::Update(MovementComponent& movementComponent, AnimationPlayerComponent& animationPlayer)
{
    myMovementDirection = { 0, 0 };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { myMovementDirection.x -= 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { myMovementDirection.y -= 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { myMovementDirection.x += 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { myMovementDirection.y += 1; }

    Utils::Orientation newOrientation = Utils::ToOrientation(myMovementDirection);
    SwitchAnimation(animationPlayer, newOrientation);

    movementComponent.SetDirection(myMovementDirection);
}

void ControlsComponent::SwitchAnimation(AnimationPlayerComponent& animationPlayer, Utils::Orientation newOrientation)
{
    if (myOrientation == newOrientation)
    {
        return;
    }

    if (myOrientation == Utils::Orientation::None)
    {
        animationPlayer.Start();
    }

    switch (newOrientation)
    {
    case Utils::Orientation::Left:
    {
        animationPlayer.SetAnimation("left_movement");
        break;
    }
    case Utils::Orientation::Top:
    {
        animationPlayer.SetAnimation("top_movement");
        break;
    }
    case Utils::Orientation::Right:
    {
        animationPlayer.SetAnimation("right_movement");
        break;
    }
    case Utils::Orientation::Bottom:
    {
        animationPlayer.SetAnimation("bottom_movement");
        break;
    }
    case Utils::Orientation::None:
    {
        animationPlayer.Pause();
        break;
    }
    }

    myOrientation = newOrientation;
}
