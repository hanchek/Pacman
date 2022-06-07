#include "GameConfig.h"

#include <Windows.h>

#include "Utils/Constants.h"

void GameConfig::WriteToFile(const std::string& filePath) const
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

void GameConfig::ReadFromFile(const std::string& filePath)
{
    const int fullscreenWidth = GetPrivateProfileIntA("Window", "FullscreenWidth", DEFAULT_WINDOW_WIDTH, filePath.c_str());
    const int fullscreenHeight = GetPrivateProfileIntA("Window", "FullscreenHeight", DEFAULT_WINDOW_HEIGHT, filePath.c_str());
    const int windowedWidth = GetPrivateProfileIntA("Window", "WindowedWidth", DEFAULT_WINDOW_WIDTH, filePath.c_str());
    const int windowedHeight = GetPrivateProfileIntA("Window", "WindowedHeight", DEFAULT_WINDOW_HEIGHT, filePath.c_str());
    fullscreenMode = sf::VideoMode(fullscreenWidth, fullscreenHeight);
    windowedMode = sf::VideoMode(windowedWidth, windowedHeight);
    isFullscreen = GetPrivateProfileIntA("Window", "IsFullscreen", DEFAULT_FULLSCREEN, filePath.c_str());
}

void GameConfig::UpdateGameWorldView(const sf::Vector2u& windowSize)
{
    const sf::FloatRect& viewPort = gameWorldView.getViewport();
    const sf::Vector2f viewSize = { windowSize.x * viewPort.width, windowSize.y * viewPort.height };

    gameWorldView.setSize(viewSize);
    gameWorldView.setCenter(viewSize.x / 2.f, viewSize.y / 2.f);
}

void GameConfig::UpdateWindowView(const sf::Vector2u& windowSize)
{
    windowView.setCenter({ windowSize.x / 2.f, windowSize.y / 2.f });
    windowView.setSize(sf::Vector2f(windowSize));
}