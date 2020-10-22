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

    sf::RenderWindow m_Window;
    sf::Sprite m_TestSprite;
};