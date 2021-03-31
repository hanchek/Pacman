#include "RenderManager.h"

#include "Game/Components/RenderComponent.h"

void RenderManager::RegisterRenderComponent(const RenderComponent* renderComponent)
{
    if (renderComponent != nullptr)
    {
        m_RenderComponents.push_back(renderComponent);
    }
    else
    {
        //[LOG] Tried to register nullptr
    }
}

void RenderManager::UnregisterRenderComponent(const RenderComponent* renderComponent)
{
    const auto foundIt = std::find(m_RenderComponents.begin(), m_RenderComponents.end(), renderComponent);
    if (foundIt != m_RenderComponents.end())
    {
        m_RenderComponents.erase(foundIt);
    }
    else
    {
        //[LOG] Tried to unregister not registered render component
    }
}

void RenderManager::Render(sf::RenderWindow& window) const
{
    for (const auto* renderComponent : m_RenderComponents)
    {
        renderComponent->Draw(window);
    }
}
