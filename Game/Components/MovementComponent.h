#pragma once

#include <SFML/System/Vector2.hpp>

class RenderComponent;

class MovementComponent
{
public:
    MovementComponent(float speed);
    
    void Update(float dt, RenderComponent& renderComponent);

    void SetVelocity(const sf::Vector2f& velocity) { myVelocity = velocity; }
    sf::Vector2f GetVelocity() const { return myVelocity; }

private:
    float mySpeed = 1.f;
    sf::Vector2f myVelocity = {0.f, 0.f};
};
