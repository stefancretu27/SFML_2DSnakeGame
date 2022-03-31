#include "Game.hpp"
#include "MainMenuState.hpp"


using namespace std;

Game& Game::getInstance()
{
    static Game game{};

    return game;
}

Game::Game()
{
    /*
    * Use the global context to set game's attributes.
    * SFML context: class RenderWindow derives from Window (Window module) and from RenderTarget (Graphics module)
    * */
    GameContext::getWindowRenderer().create(sf::VideoMode( GameContext::mWindowWidth, GameContext::mWindowHeight), "2D Snake Game");

    GameContext::getStatesManager().addState(make_unique<MainMenuState>());
}

void Game::runGame()
{
    //clock starts automatically immediately upon construction
    sf::Clock clock;
    sf::Time timeSinceLastFrame{sf::Time::Zero};

    while (GameContext::getWindowRenderer().isOpen())
    {
        //compute the elapsed time each time it is entered this while loop
        timeSinceLastFrame += clock.restart();

        //if the elapsed time sums up to mTimePerFrame, perform the update of the window
        while(timeSinceLastFrame > mTimePerFrame)
        {
            timeSinceLastFrame -= mTimePerFrame;

            // before update cycle begins, change the state
            GameContext::getStatesManager().processStateChange();
            // allow the newly changed state to handle input events (clocks, keyboard etc)
            GameContext::getStatesManager().getCurrentState()->processInput();
            // perform all calculation afferent to newly changed state
            GameContext::getStatesManager().getCurrentState()->updateState(mTimePerFrame);
            // draw on the render window the geometric shapes corresponding to newly changed state
            GameContext::getStatesManager().getCurrentState()->drawState();
        }
    }
}