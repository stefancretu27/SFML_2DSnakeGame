#include "GameContext.hpp"

#include <unistd.h>

GenericGameEngine::AssetManager& GameContext::getAssetsManager()
{
    static GenericGameEngine::AssetManager assetManager;

    return assetManager;
}

GenericGameEngine::StateManager& GameContext::getStatesManager()
{
    static GenericGameEngine::StateManager stateManager;

    return stateManager;
}

sf::RenderWindow& GameContext::getWindowRenderer()
{
    static sf::RenderWindow windowRenderer;

    return windowRenderer;
}

std::string GameContext::getAssetsPath() 
{
    return "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\";
}