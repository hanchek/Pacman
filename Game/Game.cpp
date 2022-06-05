#include "Game.h"

#include <cassert>
#include <Windows.h>

#include "Components/RenderComponent.h"
#include "EntityComponentSystem/EntityComponentManager.h"
#include "Render/RenderManager.h"
#include "ResourceManager/ResourceManager.h"
#include "Utils/Constants.h"

void Game::Run()
{
    GameInit();

    EntityID testEntity;
    if (auto componentManager = NewEntityComponentManager::GetInstance())
    {
        testEntity = componentManager->CreateEntity();
        RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(testEntity, "bomb_high_res");
        renderComponent.SetSize({ 64.f, 64.f });
    }

    sf::Clock clock;
    sf::Time dt;
    while (m_Window.isOpen())
    {
        dt = clock.restart();
        Update(dt.asSeconds());
        Render();
    }

    if (auto componentManager = NewEntityComponentManager::GetInstance())
    {
        componentManager->DestroyEntity(testEntity);
    }

    GameRelease();
}

void Game::GameInit()
{
    ResourceManager::CreateInstance();
    RenderManager::CreateInstance();
    NewEntityComponentManager::CreateInstance();

    m_GameConfig.ReadFromFile(SETTINGS_FILE_PATH);

    if (ResourceManager* resourceManager = ResourceManager::GetInstance())
    {
        resourceManager->PreloadTexturesFromFolder(TEXTURES_FOLDER_PATH);
    }

    if (m_GameConfig.isFullscreen)
    {
        if (m_GameConfig.fullscreenMode.isValid())
        {
            m_Window.create(m_GameConfig.fullscreenMode, WINDOW_NAME, sf::Style::Fullscreen);
        }
        else
        {
            const std::vector<sf::VideoMode>& videoModes = sf::VideoMode::getFullscreenModes();
            assert(!videoModes.empty() && "There should be available video mode");
            m_Window.create(videoModes[0], WINDOW_NAME, sf::Style::Fullscreen);
        }
    }
    else
    {
        m_Window.create(m_GameConfig.windowedMode, WINDOW_NAME, sf::Style::Default);
    }

    m_GameConfig.windowView = m_Window.getDefaultView();
    m_GameConfig.gameWorldView.setViewport(m_GameConfig.gameWorldViewPort);
    m_GameConfig.UpdateGameWorldView(m_Window.getSize());
}

void Game::Update(float dt)
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_Window.close();
            break;
        }
        case sf::Event::Resized:
        {
            if (!m_GameConfig.isFullscreen)
            {
                m_GameConfig.windowedMode = sf::VideoMode(event.size.width, event.size.height);
                m_GameConfig.UpdateWindowView(m_Window.getSize());
                m_GameConfig.UpdateGameWorldView(m_Window.getSize());
                m_GameConfig.WriteToFile(SETTINGS_FILE_PATH);
            }
            break;
        }
        }  
    }

    if (auto* ecs = NewEntityComponentManager::GetInstance())
    {
        ecs->Update(dt);
    }
}

void Game::Render()
{
    m_Window.clear();

    if (auto componentManager = NewEntityComponentManager::GetInstance())
    {
        m_Window.setView(m_GameConfig.gameWorldView);
        m_Window.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("worldBackground")));
        componentManager->Render(m_Window);
        m_Window.setView(m_GameConfig.windowView);
    }

    m_Window.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("button")));

    m_Window.display();
}

void Game::GameRelease()
{
    NewEntityComponentManager::DestroyInstance();
    RenderManager::DestroyInstance();
    ResourceManager::DestroyInstance();
}

void Game::GameConfig::WriteToFile(const std::string& filePath) const
{
    std::string buffer;

    buffer = std::to_string(fullscreenMode.width);
    WritePrivateProfileStringA("Window", "FullscreenWidth", buffer.c_str(), filePath.c_str());

    buffer = std::to_string(fullscreenMode.height);
    WritePrivateProfileStringA("Window", "FullscreenHeight", buffer.c_str(), filePath.c_str());

    buffer = std::to_string(windowedMode.width);
    WritePrivateProfileStringA("Window", "WindowedWidth", buffer.c_str(), filePath.c_str());

    buffer = std::to_string(windowedMode.height);
    WritePrivateProfileStringA("Window", "WindowedHeight", buffer.c_str(), filePath.c_str());

    buffer = std::to_string(static_cast<int>(isFullscreen));
    WritePrivateProfileStringA("Window", "IsFullscreen", buffer.c_str(), filePath.c_str());
}

void Game::GameConfig::ReadFromFile(const std::string& filePath)
{
    const int fullscreenWidth = GetPrivateProfileIntA("Window", "FullscreenWidth", DEFAULT_WINDOW_WIDTH, filePath.c_str());
    const int fullscreenHeight = GetPrivateProfileIntA("Window", "FullscreenHeight", DEFAULT_WINDOW_HEIGHT, filePath.c_str());
    const int windowedWidth = GetPrivateProfileIntA("Window", "WindowedWidth", DEFAULT_WINDOW_WIDTH, filePath.c_str());
    const int windowedHeight = GetPrivateProfileIntA("Window", "WindowedHeight", DEFAULT_WINDOW_HEIGHT, filePath.c_str());
    fullscreenMode = sf::VideoMode(fullscreenWidth, fullscreenHeight);
    windowedMode = sf::VideoMode(windowedWidth, windowedHeight);
    isFullscreen = GetPrivateProfileIntA("Window", "IsFullscreen", DEFAULT_FULLSCREEN, filePath.c_str());
}

void Game::GameConfig::UpdateGameWorldView(const sf::Vector2u& windowSize)
{
    const sf::FloatRect& viewPort = gameWorldView.getViewport();
    const sf::Vector2f viewSize = { windowSize.x * viewPort.width, windowSize.y * viewPort.height };

    gameWorldView.setSize(viewSize);
    gameWorldView.setCenter(viewSize.x / 2.f, viewSize.y / 2.f);
}

void Game::GameConfig::UpdateWindowView(const sf::Vector2u& windowSize)
{
    windowView.setCenter({ windowSize.x / 2.f, windowSize.y / 2.f });
    windowView.setSize(sf::Vector2f(windowSize));
}
