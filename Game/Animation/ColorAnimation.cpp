#include "Game/pch.h"
#include "ColorAnimation.h"

#include "Game/Components/RenderComponent.h"

ColorAnimation::ColorAnimation(const sf::Color& startColor, const sf::Color& endColor)
    :myStartColor(startColor),
    myEndColor(endColor)
{
}

void ColorAnimation::ApplyAnimation(float t, RenderComponent& renderComponent) const
{
    renderComponent.SetColor(Utils::Lerp(myStartColor, myEndColor, t));
}
