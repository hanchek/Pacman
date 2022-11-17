#include "Game/pch.h"
#include "ColorAnimationComponent.h"

#include "Game/Components/RenderComponent.h"

ColorAnimationComponent::ColorAnimationComponent(const sf::Color& start, const sf::Color& end, float duration)
    : onAnimationEnd(myAnimationEndSignal),
    myStartColor(start),
    myEndColor(end),
    myDuration(duration)
{
}

void ColorAnimationComponent::Update(float dt, RenderComponent& renderComponent)
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

    renderComponent.SetColor(Utils::Lerp(myStartColor, myEndColor, myTime / myDuration));
}
