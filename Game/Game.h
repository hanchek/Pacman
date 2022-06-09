#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

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

    GameConfig myGameConfig;
    sf::RenderWindow myWindow;
};