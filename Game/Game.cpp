#include "Game/pch.h"
#include "Game.h"

#include "Engine/Components/AnimationPlayerComponent.h"
#include "Engine/Components/RenderComponent.h"
#include "Engine/EntityComponentSystem/EntityComponentManager.h"
#include "Engine/ResourceManager/ResourceManager.h"

#include "Game/Test.h"

void Game::Run()
{
    GameInit();

    Test::CreateBackGround();

    sf::Clock clock;
    sf::Time dt;
    while (myWindow.isOpen())
    {
        dt = clock.restart();
        Update((std::min)(dt.asSeconds(), FRAME_TIME));
        Render();
    }

    GameRelease();
}

void Game::GameInit()
{
    ResourceManager::CreateInstance();
    EntityComponentManager::CreateInstance();

    myGameConfig.ReadFromFile(SETTINGS_FILE_PATH);

    ResourceManager::GetInstance()->PreloadTexturesFromFolder(TEXTURES_FOLDER_PATH);

    if (myGameConfig.isFullscreen)
    {
        if (myGameConfig.fullscreenMode.isValid())
        {
            myWindow.create(myGameConfig.fullscreenMode, WINDOW_NAME, sf::Style::Fullscreen);
        }
        else
        {
            const std::vector<sf::VideoMode>& videoModes = sf::VideoMode::getFullscreenModes();
            assert(!videoModes.empty() && "There should be available video mode");
            myWindow.create(videoModes[0], WINDOW_NAME, sf::Style::Fullscreen);
        }
    }
    else
    {
        myWindow.create(myGameConfig.windowedMode, WINDOW_NAME, sf::Style::Default);
    }

    myGameConfig.windowView = myWindow.getDefaultView();
    myGameConfig.gameWorldView.setViewport(myGameConfig.gameWorldViewPort);
    myGameConfig.UpdateGameWorldView(myWindow.getSize());
}

void Game::Update(float dt)
{
    sf::Event event;
    while (myWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            myWindow.close();
            break;
        }
        case sf::Event::Resized:
        {
            if (!myGameConfig.isFullscreen)
            {
                myGameConfig.windowedMode = sf::VideoMode(event.size.width, event.size.height);
                myGameConfig.UpdateWindowView(myWindow.getSize());
                myGameConfig.UpdateGameWorldView(myWindow.getSize());
                myGameConfig.WriteToFile(SETTINGS_FILE_PATH);
            }
            break;
        }
        }  
    }

    auto componentManager = EntityComponentManager::GetInstance();

    auto animationPlayerUpdate = [dt](AnimationPlayerComponent& animPlayerComp, RenderComponent& renderComponent)
    {
        animPlayerComp.Update(dt, renderComponent);
    };
    componentManager->ForEachComponent<AnimationPlayerComponent, RenderComponent>(animationPlayerUpdate);

    const bool isAnyEntityDestroyed = componentManager->DestroyMarkedEntities();
    if (isAnyEntityDestroyed)
    {
        componentManager->Sort<RenderComponent>([](const auto& lhs, const auto& rhs) {
            return lhs.GetRenderOrder() < rhs.GetRenderOrder();
        });
    }
}

void Game::Render()
{
    myWindow.clear();

    //gameworld render section begin
    myWindow.setView(myGameConfig.gameWorldView);

    {
        auto componentManager = EntityComponentManager::GetInstance();
        componentManager->ForEachComponent<RenderComponent>([&m_Window = myWindow](RenderComponent& renderComponent) {
            renderComponent.Draw(m_Window);
        });
    }
    // gameworld render section end

    //UI render section begin
    myWindow.setView(myGameConfig.windowView);

    Test::DrawMissingTexture(myWindow);
    // UI render section end

    myWindow.display();
}

void Game::GameRelease()
{
    EntityComponentManager::DestroyInstance();
    ResourceManager::DestroyInstance();
}
