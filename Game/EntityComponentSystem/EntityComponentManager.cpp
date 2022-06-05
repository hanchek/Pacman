#include "EntityComponentManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Game/Components/RenderComponent.h"

EntityID NewEntityComponentManager::CreateEntity()
{
    return myRegistry.create();
}

void NewEntityComponentManager::DestroyEntity(EntityID entityID)
{
    myRegistry.destroy(entityID);
}

bool NewEntityComponentManager::IsEntityValid(EntityID entityID) const
{
    return myRegistry.valid(entityID);
}

void NewEntityComponentManager::AddUpdateTask(UpdateTask task)
{
    myTasks.push_back(std::move(task));
}

void NewEntityComponentManager::Update(float dt)
{
    for (const auto& task : myTasks)
    {
        task(dt, myRegistry);
    }
}

void NewEntityComponentManager::Render(sf::RenderWindow& window)
{
    auto view = myRegistry.view<RenderComponent>();

    view.each([&window](RenderComponent& renderComponent) {
        renderComponent.Draw(window);
    });
}
