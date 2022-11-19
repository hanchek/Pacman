#pragma once

#include <SFML/Graphics/Color.hpp>

#include "Animation.h"

class ColorAnimation : public Animation
{
public:
    ColorAnimation(const sf::Color& startColor, const sf::Color& endColor);

    void ApplyAnimation(float t, RenderComponent& renderComponent) const override;

private:
    sf::Color myStartColor;
    sf::Color myEndColor;
};