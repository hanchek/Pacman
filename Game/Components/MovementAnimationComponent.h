#pragma once

#include "AnimationComponent.h"
#include "Game/Utils/Utils.h"

class MovementComponent;

struct MovementAnimationFrames
{
    std::vector<sf::Vector2i> leftFrames;
    std::vector<sf::Vector2i> topFrames;
    std::vector<sf::Vector2i> rightFrames;
    std::vector<sf::Vector2i> bottomFrames;
};

class MovementAnimationComponent
{
public:

    MovementAnimationComponent(MovementAnimationFrames&& frames, float duration);
    MovementAnimationComponent(std::vector<sf::Vector2i>&& leftFrames,
        std::vector<sf::Vector2i>&& topFrames, std::vector<sf::Vector2i>&& rightFrames,
        std::vector<sf::Vector2i>&& bottomFrames, float duration);

    void Update(float dt, const MovementComponent& movementComponent, RenderComponent& renderComponet);

private:
    AnimationComponent myLeftAnimation;
    AnimationComponent myTopAnimation;
    AnimationComponent myRightAnimation;
    AnimationComponent myBottomAnimation;
};
