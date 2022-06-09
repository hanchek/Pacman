#include "Game/pch.h"
#include "MovementComponent.h"

#include "RenderComponent.h"

MovementComponent::MovementComponent(float speed) : mySpeed(speed)
{
}

void MovementComponent::Update(float dt, RenderComponent& renderComponent)
{
    renderComponent.MovePosition(myVelocity * (dt * mySpeed));
}
