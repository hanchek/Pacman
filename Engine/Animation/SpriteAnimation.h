#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Animation.h"

class RenderComponent;

class SpriteAnimation : public Animation
{
public:
    SpriteAnimation(std::vector<sf::Vector2i>&& myFrames);

    void ApplyAnimation(float t, RenderComponent& renderComponent) const override;

private:
    std::vector<sf::Vector2i> myFramesPositions;
};