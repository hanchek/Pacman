#pragma once

#include <SFML/System/Vector2.hpp>

namespace Utils
{
    enum class Orientation
    {
        Left,
        Top,
        Right,
        Bottom,
        None
    };

    // returns true if the value was out of boundries false otherwise
    template<typename T>
    bool ClampVector(sf::Vector2<T>& inout, const sf::Vector2<T>& topleft, const sf::Vector2<T>& downright)
    {
        const T& clampedX = std::clamp(inout.x, topleft.x, downright.x);
        const T& clampedY = std::clamp(inout.y, topleft.y, downright.y);

        if (clampedX == inout.x && clampedY == inout.y)
        {
            return false;
        }

        inout = { clampedX, clampedY };

        return true;
    }

    sf::Vector2i GetNearestTile(const sf::Vector2f& position);

    sf::Vector2f GetTilePosition(const sf::Vector2i& tile);

    //returns sign of the number: 1.f, 0.f, -1.f
    float Sign(float number);

    // returns the difference between in and out values
    float ReduceAbs(float& inout, float subtractor);

    // returns the difference between in and out values
    float Clamp(float& inout, float leftBorder, float rightBorder);

    Orientation ToOrientation(const sf::Vector2i& vector);
}
