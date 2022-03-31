#pragma once

#include "GameEngine/State.hpp"
#include "GameContext.hpp"

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameOverState : public GenericGameEngine::State
{
    public:
        GameOverState();
        ~GameOverState() = default;

        GameOverState(const GameOverState&) = delete;
        GameOverState& operator=(const GameOverState&) = delete;

        void initState() override;
        void processInput() override;
        void updateState(sf::Time elapsedTimeSinceLastUpdate) override;
        void drawState() override;

    private:
        sf::Text mGameOverTitle;
        sf::Text mGameOverMessage;
        sf::Text mReplayButton;
        sf::Text mExitButton;
        sf::Sprite mBackground;

        bool mIsReplayButtonSelected;
        bool mIsReplayButtonPressed;
        
        bool mIsExitButtonSelected;
        bool mIsExitButtonPressed;
};
