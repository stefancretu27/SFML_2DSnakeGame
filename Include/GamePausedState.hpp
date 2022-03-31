#pragma once

#include "GameEngine/State.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class GamePausedState: public GenericGameEngine::State
{
    public:
        GamePausedState() = default;
        ~GamePausedState() = default;

        GamePausedState(const GamePausedState&) = delete;
        GamePausedState& operator=(const GamePausedState&) = delete;

        void initState() override;
        void processInput() override;
        void updateState(sf::Time elapsedTimeSinceLastUpdate) override;
        void drawState() override;

    private:
        sf::Text mPauseTitle;
};