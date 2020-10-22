#include "Game.h"
#include "ResourceManager/ResourceManager.h"

void Game::Run()
{
    GameInit();

    sf::Clock clock;
    sf::Time dt; 
    while (m_Window.isOpen())
    {
        dt = clock.restart();
        Update(dt.asSeconds());
        Render();
    }

    GameRelease();
}

void Game::GameInit()
{
    m_Window.create(sf::VideoMode(200, 200), "My game works!");
    ResourceManager::PreloadTexturesFromFolder("Data/Textures");

    m_TestSprite.setTexture(ResourceManager::GetTexture("testTexture"));
}

void Game::Update(float dt)
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_Window.close();
    }
}

void Game::Render()
{
    m_Window.clear();

    m_Window.draw(m_TestSprite);

    m_Window.display();
}

void Game::GameRelease()
{
    ResourceManager::ReleaseResources();
}
