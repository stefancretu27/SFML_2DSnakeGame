#pragma once

#include "GameEngine/State.hpp"
#include "GameContext.hpp"

#include <memory>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

class MainMenuState: public GenericGameEngine::State
{
    public:
        MainMenuState();
        ~MainMenuState() = default;

        MainMenuState(const MainMenuState&) = delete;
        MainMenuState& operator=(const MainMenuState&) = delete;

        void initState() override;
        void processInput() override;
        void updateState(sf::Time elapsedTimeSinceLastUpdate) override;
        void drawState() override;

    private:
        sf::Text mGameTitle;
        sf::Text mPlayButton;
        sf::Text mExitButton;
        sf::Text mGameRulesButton;
        sf::Sprite mBackground;

        bool mIsPlayButtonSelected;
        bool mIsPlayButtonPressed;
        
        bool mIsExitButtonSelected;
        bool mIsExitButtonPressed;

        bool mIsGameRulesButtonSelected;
        bool mIsGameRulesButtonPressed;

        sf::Texture mLogoPieceTexture;
        float mSnakeTextureSize;
        std::vector<sf::Sprite> mLogo;
};