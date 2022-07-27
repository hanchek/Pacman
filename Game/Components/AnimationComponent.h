#pragma once

#include <vector>

#include <entt/signal/sigh.hpp>

#include <SFML/System/Vector2.hpp>

namespace sf
{
    class RenderWindow;
}

class RenderComponent;

class AnimationComponent
{
public:
    using AnimCallback = void();
    using AnimSink = entt::sink<entt::sigh<AnimCallback>>;

    AnimSink onAnimationEnd;

    AnimationComponent(std::vector<sf::Vector2i>&& frames, float duration);

    void SetIsRepeatable(bool isRepeatable) { myIsRepeatable = isRepeatable; }
    bool GetIsRepeatable() const { return myIsRepeatable; }

    void Update(float dt, RenderComponent& component);

private:
    std::vector<sf::Vector2i> myFramesPositions;
    float myDuration = 0.f;
    float myTime = 0.f;
    bool myIsRepeatable = true;
    bool myIsPaused = false;
    entt::sigh<AnimCallback> myAnimationEndSignal;
};