#include "Game/pch.h"
#include "AnimationPlayerComponent.h"

#include "Game/Animation/Animation.h"
#include "Game/ResourceManager/ResourceManager.h"

AnimationPlayerComponent::AnimationPlayerComponent(float duration)
    :onAnimationEnd(myAnimationEndSignal),
    myDuration(duration)   
{
}

AnimationPlayerComponent::AnimationPlayerComponent(float duration, const std::string& animationName)
    : onAnimationEnd(myAnimationEndSignal),
    myDuration(duration)
{
    myAnimation = ResourceManager::GetInstance()->GetAnimation(animationName);
}

void AnimationPlayerComponent::Update(float dt, RenderComponent& renderComponent)
{
    if (myAnimation == nullptr || myIsPaused)
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

    myAnimation->ApplyAnimation(myTime / myDuration, renderComponent);
}
