#include "pch.h"
#include "AnimationPlayerComponent.h"

#include "Animation/Animation.h"
#include "ResourceManager/ResourceManager.h"

AnimationPlayerComponent::AnimationPlayerComponent(float duration)
    :onAnimationEnd(myAnimationEndSignal),
    myDuration(duration)   
{
}

AnimationPlayerComponent::AnimationPlayerComponent(float duration, const std::string& animationName)
    : onAnimationEnd(myAnimationEndSignal),
    myDuration(duration)
{
    SetAnimation(animationName);
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

void AnimationPlayerComponent::SetAnimation(const std::string& animationName)
{
    myAnimation = ResourceManager::GetInstance()->GetAnimation(animationName);
}
