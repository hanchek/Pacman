#include "Game/pch.h"
#include "StaticWallComponent.h"

#include "Engine/Components/RenderComponent.h"

void StaticWallComponent::Init(RenderComponent& renderComponent)
{
    myTile = Utils::GetNearestTile(renderComponent.GetPosition());
}
