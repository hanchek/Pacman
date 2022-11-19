#include "Game/pch.h"
#include "SpriteAnimation.h"

#include "Game/Components/RenderComponent.h"

SpriteAnimation::SpriteAnimation(std::vector<sf::Vector2i>&& framesPositions)
    :myFramesPositions(std::move(framesPositions))
{
}

void SpriteAnimation::ApplyAnimation(float t, RenderComponent& renderComponent) const
{
    const int frameIndex = std::trunc(t * myFramesPositions.size());

    renderComponent.SetTextureRectPosition(myFramesPositions[frameIndex]);
}
