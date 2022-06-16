#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

namespace sf
{
    class RenderWindow;
}

class RenderComponent;

class AnimationComponent
{
public:
    AnimationComponent(std::vector<sf::Vector2i>&& frames, float duration);

    void Update(float dt, RenderComponent& component);

private:
    std::vector<sf::Vector2i> myFramesPositions;
    float myDuration = 0.f;
    float myTime = 0.f;
};