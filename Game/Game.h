#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    void Run();
private:
    void GameInit();
    void Update(float dt);
    void Render();
    void GameRelease();

    struct GameConfig
    {
        sf::VideoMode fullscreenMode = sf::VideoMode(800, 600);
        sf::VideoMode windowedMode = sf::VideoMode(800, 600);
        bool isFullscreen = true;

        void WriteToFile(const std::string& filePath) const;
        void ReadFromFile(const std::string& filePath);
    };

    GameConfig m_GameConfig;
    sf::RenderWindow m_Window;
};