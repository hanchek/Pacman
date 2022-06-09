#include "Game/pch.h"
#include "Game.h"

#include "Components/ControlsComponent.h"
#include "Components/MovementComponent.h"
#include "Components/RenderComponent.h"
#include "EntityComponentSystem/EntityComponentManager.h"
#include "ResourceManager/ResourceManager.h"

void Game::Run()
{
    GameInit();

    EntityID testEntity;

    {
        auto componentManager = EntityComponentManager::GetInstance();

        testEntity = componentManager->CreateEntity();
        RenderComponent& renderComponent = componentManager->CreateComponent<RenderComponent>(testEntity, "bomb_high_res");
        renderComponent.SetSize({ 64.f, 64.f });
        componentManager->CreateComponent<MovementComponent>(testEntity, 100.f);
        componentManager->CreateComponent<ControlsComponent>(testEntity);
    }

    sf::Clock clock;
    sf::Time dt;
    while (myWindow.isOpen())
    {
        dt = clock.restart();
        Update(dt.asSeconds());
        Render();
    }

    EntityComponentManager::GetInstance()->DestroyEntity(testEntity);

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

    componentManager->ForEachComponent<ControlsComponent, MovementComponent>(&ControlsComponent::Update);

    auto movementUpdate = [dt](MovementComponent& movementComponent, RenderComponent& renderComponent) {
        movementComponent.Update(dt, renderComponent);
    };
    componentManager->ForEachComponent<MovementComponent, RenderComponent>(movementUpdate);
}

void Game::Render()
{
    myWindow.clear();

    //gameworld render section begin
    myWindow.setView(myGameConfig.gameWorldView);
    myWindow.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("worldBackground")));
        
    {
        auto componentManager = EntityComponentManager::GetInstance();
        componentManager->ForEachComponent<RenderComponent>([&m_Window = myWindow](RenderComponent& renderComponent) {
            renderComponent.Draw(m_Window);
        });
    }
    // gameworld render section end

    //UI render section begin
    myWindow.setView(myGameConfig.windowView);

    myWindow.draw(sf::Sprite(ResourceManager::GetInstance()->GetTexture("button")));
    // UI render section end

    myWindow.display();
}

void Game::GameRelease()
{
    EntityComponentManager::DestroyInstance();
    ResourceManager::DestroyInstance();
}
