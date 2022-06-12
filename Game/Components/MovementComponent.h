#pragma once

#include <SFML/System/Vector2.hpp>

class RenderComponent;

class MovementComponent
{
public:
    MovementComponent(float speed);
    
    void Update(float dt, RenderComponent& renderComponent);

    void SetDirection(const sf::Vector2i& velocity) { myDirection = velocity; }
    sf::Vector2i GetDirection() const { return myDirection; }
    sf::Vector2f GetDirectionF() const { return { float(myDirection.x), float(myDirection.y) }; }

private:
    float mySpeed = 1.f;
    sf::Vector2i myDirection = { 0, 0 };
};
