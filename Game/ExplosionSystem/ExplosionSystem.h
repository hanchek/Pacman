#include <SFML/System/Vector2.hpp>

namespace ExplosionSystem
{
    std::vector<sf::Vector2i> GetImpactedTiles(int power, const sf::Vector2i& tilePosition);

    void SpawnExplosion(int power, const sf::Vector2i& tilePosition);
}
