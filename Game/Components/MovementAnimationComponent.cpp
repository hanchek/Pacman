#include "Game\pch.h"
#include "MovementAnimationComponent.h"

#include "MovementComponent.h"
#include "RenderComponent.h"

MovementAnimationComponent::MovementAnimationComponent(MovementAnimationFrames&& frames, float duration)
    : myLeftAnimation(std::move(frames.leftFrames), duration),
    myTopAnimation(std::move(frames.topFrames), duration),
    myRightAnimation(std::move(frames.rightFrames), duration),
    myBottomAnimation(std::move(frames.bottomFrames), duration)
{
}

MovementAnimationComponent::MovementAnimationComponent(
    std::vector<sf::Vector2i>&& leftFrames,
    std::vector<sf::Vector2i>&& topFrames,
    std::vector<sf::Vector2i>&& rightFrames,
    std::vector<sf::Vector2i>&& bottomFrames,
    float duration)
    : myLeftAnimation(std::move(leftFrames), duration),
    myTopAnimation(std::move(topFrames), duration),
    myRightAnimation(std::move(rightFrames), duration),
    myBottomAnimation(std::move(bottomFrames), duration)
{
}

void MovementAnimationComponent::Update(float dt, const MovementComponent& movementComponent, RenderComponent& renderComponet)
{
    switch (Utils::ToOrientation(movementComponent.GetDirection()))
    {
    case Utils::Orientation::Left: { myLeftAnimation.Update(dt, renderComponet); break; }
    case Utils::Orientation::Top: { myTopAnimation.Update(dt, renderComponet); break; }
    case Utils::Orientation::Right: { myRightAnimation.Update(dt, renderComponet); break; }
    case Utils::Orientation::Bottom: { myBottomAnimation.Update(dt, renderComponet); break; }
    default: { break; }
    }
}
