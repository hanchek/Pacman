#include "Game\pch.h"
#include "AnimationComponent.h"

#include "RenderComponent.h"

AnimationComponent::AnimationComponent(std::vector<sf::Vector2i>&& frames, float duration)
    : onAnimationEnd(myAnimationEndSignal)
{
    myFramesPositions = std::move(frames);
    myDuration = duration;
}

void AnimationComponent::Update(float dt, RenderComponent& component)
{
    if (myIsPaused)
    {
        return;
    }

    myTime += dt;

    if (myTime - myDuration > -EPS)
    {
        if (myIsRepeatable)
        {
            myTime -= myDuration;
        }
        else
        {
            myTime = 0.f;
            myIsPaused = true;
            myAnimationEndSignal.publish();
            return;
        }
    }

    const int frameIndex = std::trunc(myTime / myDuration * myFramesPositions.size());

    component.SetTextureRectPosition(myFramesPositions[frameIndex]);
}
