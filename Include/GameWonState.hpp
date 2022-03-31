#pragma once

#include "GameEngine/State.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

class GameWonState: public GenericGameEngine::State
{
    public:
        GameWonState();
        ~GameWonState() = default;

        GameWonState(const GameWonState&) = delete;
        GameWonState& operator=(const GameWonState&) = delete;

        void initState() override;
        void processInput() override;
        void updateState(sf::Time elapsedTimeSinceLastUpdate) override;
        void drawState() override;

    private:
        sf::Text mWinTitle;
        sf::Text mReplayButton;
        sf::Text mExitButton;
        sf::Sprite mBackground;

        bool mIsReplayButtonSelected;
        bool mIsReplayButtonPressed;
        
        bool mIsExitButtonSelected;
        bool mIsExitButtonPressed;

        sf::Music mBackgroundMusic;
        static constexpr float mDefaultMusicVolume{34.f};
};