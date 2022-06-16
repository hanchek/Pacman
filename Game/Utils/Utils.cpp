#include "Game/pch.h"
#include "Utils.h"

namespace Utils
{
    bool ClampVector(sf::Vector2i& inout, const sf::Vector2i& topleft, const sf::Vector2i& downright)
    {
        const int& clampedX = std::clamp(inout.x, topleft.x, downright.x);
        const int& clampedY = std::clamp(inout.y, topleft.y, downright.y);

        if (clampedX == inout.x && clampedY == inout.y)
        {
            return false;
        }

        inout = { clampedX, clampedY };

        return true;
    }

    sf::Vector2i GetNearestTile(const sf::Vector2f& position)
    {
        return { int(position.x / MAP_SCALE), int(position.y / MAP_SCALE) };
    }

    sf::Vector2f GetTilePosition(const sf::Vector2i& tile)
    {
        return { tile.x * MAP_SCALE + MAP_SCALE / 2.f, tile.y * MAP_SCALE + MAP_SCALE / 2.f };
    }

    float Sign(float number)
    {
        if (fabs(number) < EPS)
        {
            return 0.f;
        }

        return (number < 0.f) ? -1.f : 1.f;
    }

    float ReduceAbs(float& inout, float subtractor)
    {
        if (fabs(inout) > subtractor)
        {
            subtractor *= Sign(inout);
        }
        else
        {
            subtractor = inout;
        }

        inout -= subtractor;
        return subtractor;
    }

    float Clamp(float& inout, float leftBorder, float rightBorder)
    {
        float leftDifference = leftBorder - inout;
        if (leftDifference > 0)
        {
            inout = leftBorder;
            return leftDifference;
        }

        float rightDifference = rightBorder - inout;
        if (rightDifference < 0)
        {
            inout = rightBorder;
            return rightDifference;
        }

        return 0.f;
    }

    Orientation ToOrientation(const sf::Vector2i& vector)
    {
        if (vector.x < 0) { return Orientation::Left; }
        if (vector.y < 0) { return Orientation::Top; }
        if (vector.x > 0) { return Orientation::Right; }
        if (vector.y > 0) { return Orientation::Bottom; }

        return Orientation::None;
    }
}


