#pragma once

#include <SFML/Graphics.hpp>

struct GameConfig
{
    sf::VideoMode fullscreenMode = sf::VideoMode(800, 600);
    sf::VideoMode windowedMode = sf::VideoMode(800, 600);
    bool isFullscreen = true;

    const sf::FloatRect gameWorldViewPort = { { 0.125f, 0.f}, {0.75f, 1.f} };
    sf::View gameWorldView;
    sf::View windowView;

    void WriteToFile(const std::string& filePath) const;
    void ReadFromFile(const std::string& filePath);

    void UpdateGameWorldView(const sf::Vector2u& windowSize);
    void UpdateWindowView(const sf::Vector2u& windowSize);
};