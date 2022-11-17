#pragma once

#include <entt/signal/sigh.hpp>

#include <SFML/Graphics/Color.hpp>

class RenderComponent;

class ColorAnimationComponent
{
public:
    using AnimCallback = void();
    using AnimSink = entt::sink<entt::sigh<AnimCallback>>;

    AnimSink onAnimationEnd;

    ColorAnimationComponent(const sf::Color& start, const sf::Color& end, float duration);

    void SetIsRepeatable(bool isRepeatable) { myIsRepeatable = isRepeatable; }
    bool GetIsRepeatable() const { return myIsRepeatable; }

    void Update(float dt, RenderComponent& renderComponent);

private:
    sf::Color myStartColor;
    sf::Color myEndColor;
    float myDuration = 0.f;
    float myTime = 0.f;
    bool myIsRepeatable = false;
    bool myIsPaused = false;
    entt::sigh<AnimCallback> myAnimationEndSignal;
};