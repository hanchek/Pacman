#pragma once

#include <SFML/Graphics.hpp>

#include "GameConfig.h"

class Game
{
public:
    void Run();
private:
    void GameInit();
    void Update(float dt);
    void Render();
    void GameRelease();

    GameConfig m_GameConfig;
    sf::RenderWindow m_Window;
};