#pragma once

#include "GameEngine/State.hpp"
#include "GameContext.hpp"
#include "Snake.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

class GamePlayState : public GenericGameEngine::State
{
    public:
        GamePlayState();
        ~GamePlayState() = default;

        void initState() override;
        void processInput() override;
        void updateState(sf::Time elapsedTimeSinceLastUpdate) override;
        void drawState() override;

    private:
        sf::Sprite mGrass;
        sf::Sprite mFood;
        sf::Sprite mCandy;
        bool isDrawCandyEnabled{false};
        std::array<sf::Sprite, 4> mWalls;
        
        float mSnakeTextureSize{};
        Snake mSnake;
        sf::Vector2f mSnakeDirection;
        sf::Time mElapsedTime;

        sf::Text mScoreText;
        int mScore{};

        sf::Text mCandyScoreText;
        int mCandyScore{};

        sf::Sound mAppleBiteSound;
        sf::Sound mSnakeStrike;
        sf::Sound mSnakeRattling;
        sf::Music mBackgroundMusic;
        bool isMusicPaused{false};
        static constexpr float mDefaultMusicVolume{34.f};

        bool drawCandy();
};