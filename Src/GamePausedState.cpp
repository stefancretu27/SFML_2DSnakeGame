#include "GamePausedState.hpp"
#include "GameContext.hpp"
#include "GamePlayState.hpp"

#include <SFML/Window/Event.hpp>


void GamePausedState::initState()
{
    // Game Paused title
    mPauseTitle.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mPauseTitle.setString("Snake game paused!");

    mPauseTitle.setOrigin( mPauseTitle.getLocalBounds().width/2, 
                          mPauseTitle.getLocalBounds().height/2);
    mPauseTitle.setPosition( GameContext::getWindowRenderer().getSize().x/2 -100.f, 
                            GameContext::getWindowRenderer().getSize().y/2 - 33.f);

    mPauseTitle.setCharacterSize(80);
    mPauseTitle.setFillColor(sf::Color::Cyan);

};

void GamePausedState::processInput()
{
    //class Event is defined in Window module and does not have a definition macro directive
    sf::Event event;
    while (GameContext::getWindowRenderer().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            GameContext::getWindowRenderer().close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // event.key.code stores the key that was lastly pressed
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                case sf::Keyboard::P:
                {
                    //remove current Paused state and go back to the previous state (play)
                    GameContext::getStatesManager().popCurrentState();
                }
                break;

                default:
                    break;
            }
        }
    }
};

void GamePausedState::updateState(sf::Time elapsedTimeSinceLastUpdate)
{
};

void GamePausedState::drawState()
{
    GameContext::getWindowRenderer().draw(mPauseTitle);
    GameContext::getWindowRenderer().display();
};