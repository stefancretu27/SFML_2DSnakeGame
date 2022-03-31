#pragma once

#include <SFML/Graphics.hpp>

class Game
{
    public:
        static Game& getInstance();
        ~Game() = default;

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        void runGame();

    private:
        Game();

        const sf::Time mTimePerFrame{sf::seconds(1.f/60.f)};
        
};
