#pragma once

#pragma once

#include "GameEngine/State.hpp"
#include "GameContext.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>
#include <array>

class GameRulesState : public GenericGameEngine::State
{
    public:
        GameRulesState();
        ~GameRulesState() = default;

        GameRulesState(const GameRulesState&) = delete;
        GameRulesState& operator=(const GameRulesState&) = delete;

        void initState() override;
        void processInput() override;
        void updateState(sf::Time elapsedTimeSinceLastUpdate) override;
        void drawState() override;

    private:
        std::array<sf::Text, 6> mGameRules;

        sf::Text mBackButton;
        sf::Sprite mBackground;

        bool mIsBackButtonSelected;
        bool mIsBackButtonPressed;

};
