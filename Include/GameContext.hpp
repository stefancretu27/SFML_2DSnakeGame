#pragma once

#include "GameEngine/AssetManager.hpp"
#include "GameEngine/StateManager.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

#include <windows.h>

#include <memory>
#include <string>

/*
* Struct defining the Game's context. It provides the manager of all assets of the game,
* as well as the manager of all states of the game. This managers are unique. Additionally,
* it encapsulates the window object, which is also unique. As all these resources are unique,
* the game context itself becomes transitively unique.
* 
* Therefore, each resoruce is created as a magic static and made accessible via a getInstance method,
* following the structure of a Singleton-like design. Thus, is ensured thread safety upon creation.
*
* The members are allocated on stack (no smart_ptr is used) as it is preferred to have each member to
* dynamically allocate the resources it uses internally.
*/
struct GameContext
{
    GameContext(const GameContext&) = delete;
    GameContext& operator=(const GameContext&) = delete;
    ~GameContext() = default;

    static GenericGameEngine::AssetManager& getAssetsManager();
    static GenericGameEngine::StateManager& getStatesManager();
    static sf::RenderWindow& getWindowRenderer();
    static std::string getAssetsPath();

    enum AssetID
    {
        MainFont,
        MainMenuBackground,
        Grass,
        Food,
        Wall,
        SnakeBody,
        LogoIcon,
        Candy,
        AppleBiteSound,
        SnakeStrikeSound,
        SnakeRattlingSound,
        AssetsNo
    };

    static constexpr unsigned int mWindowHeight{840};
    static constexpr unsigned int mWindowWidth{1200};
};