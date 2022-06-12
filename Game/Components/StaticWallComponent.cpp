#include "Game\pch.h"
#include "StaticWallComponent.h"

#include "RenderComponent.h"

void StaticWallComponent::Init(RenderComponent& renderComponent)
{
    myTile = Utils::GetNearestTile(renderComponent.GetPosition());
}
