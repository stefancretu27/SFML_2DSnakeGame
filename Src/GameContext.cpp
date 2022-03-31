#include "GameContext.hpp"


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