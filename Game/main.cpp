#include <SFML/Graphics.hpp>
#include "ResourceManager/ResourceManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    ResourceManager::PreloadTexturesFromFolder("Data/Textures");

    sf::Sprite testSprite;
    testSprite.setTexture(ResourceManager::GetTexture("testTexture"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(testSprite);
        window.display();
    }

    ResourceManager::ReleaseResources();

    return 0;
}