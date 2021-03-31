#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Game/Singleton.h"

class RenderComponent;

class RenderManager:public Singleton<RenderManager>
{
public:
    friend Singleton<RenderManager>;

    void RegisterRenderComponent(const RenderComponent* renderComponent);
    void UnregisterRenderComponent(const RenderComponent* renderComponent);
    void Render(sf::RenderWindow& window) const;
    const std::vector<const RenderComponent*>& GetRenderComponents() { return m_RenderComponents; }

private:
    RenderManager() = default;
    ~RenderManager() = default;

    std::vector<const RenderComponent*> m_RenderComponents;
};