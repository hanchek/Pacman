#pragma once

#include <vector>

#include <entt/signal/sigh.hpp>

class Animation;
class RenderComponent;

class AnimationPlayerComponent
{
public:
    using AnimCallback = void();
    using AnimSink = entt::sink<entt::sigh<AnimCallback>>;

    AnimSink onAnimationEnd;

    AnimationPlayerComponent(float duration);
    AnimationPlayerComponent(float duration, const std::string& animationName);

    void Update(float dt, RenderComponent& renderComponent);

    void Pause() { myIsPaused = true; }
    void Start() { myIsPaused = false; }
    void Restart() { myTime = 0.f; Start(); }

    void SetIsRepeatable(bool isRepeatable) { myIsRepeatable = isRepeatable; }
    bool GetIsRepeatable() const { return myIsRepeatable; }

    void SetAnimation(const Animation* animation) { myAnimation = animation; }

private:
    bool myIsPaused = false;
    bool myIsRepeatable = true;
    float myTime = 0.f;
    float myDuration = 0.f;

    const Animation* myAnimation = nullptr;

    entt::sigh<AnimCallback> myAnimationEndSignal;
};