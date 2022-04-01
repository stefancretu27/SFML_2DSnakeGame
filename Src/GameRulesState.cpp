#include "GameRulesState.hpp"
#include "GameContext.hpp"
#include "GamePlayState.hpp"

#include <SFML/Window/Event.hpp>

GameRulesState::GameRulesState(): mIsBackButtonSelected{false},
                                   mIsBackButtonPressed{false}
{}

void GameRulesState::initState() 
{
    mBackground.setTexture(GameContext::getAssetsManager().getTexture(GameContext::MainMenuBackground));
    mBackground.setTextureRect(GameContext::getWindowRenderer().getViewport(GameContext::getWindowRenderer().getDefaultView()));

    for(size_t idx{0}; idx < mGameRules.size(); ++idx)
    {
        mGameRules[idx].setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
        mGameRules[idx].setCharacterSize(40);
        mGameRules[idx].setFillColor(sf::Color::Black);
    }

    mGameRules[0].setString("    1. The snake can be moved around using W,A,S,D or arrows keys.");
    mGameRules[0].setOrigin( mGameRules[0].getLocalBounds().width/10, 
                             mGameRules[0].getLocalBounds().height/10);
    mGameRules[0].setPosition( GameContext::getWindowRenderer().getSize().x/7, 
                               GameContext::getWindowRenderer().getSize().y/7);

    mGameRules[1].setString("    2. The game is over if the snake bites itself or hits the wall that surrounds the playground.");
    mGameRules[1].setOrigin( mGameRules[0].getLocalBounds().width/10, 
                             mGameRules[0].getLocalBounds().height/10);
    mGameRules[1].setPosition( GameContext::getWindowRenderer().getSize().x/7, 
                               GameContext::getWindowRenderer().getSize().y/7 + 50.f);

    const char *s2 = "    3. The snake's mission is to eat the apples spawned randomly on the playground. When it does so, \n \
        an apple bite sound can be heard";
    mGameRules[2].setString(std::string(s2));
    mGameRules[2].setOrigin( mGameRules[0].getLocalBounds().width/10, 
                             mGameRules[0].getLocalBounds().height/10);
    mGameRules[2].setPosition( GameContext::getWindowRenderer().getSize().x/7, 
                               GameContext::getWindowRenderer().getSize().y/7 + 100.f);

    const char *s3 = "    4. The game can be paused/unpaused by pressing Esc or P. Automatically, the background \n \
        music stops/restarts.";
    mGameRules[3].setString(std::string(s3));
    mGameRules[3].setOrigin( mGameRules[0].getLocalBounds().width/10, 
                             mGameRules[0].getLocalBounds().height/10);
    mGameRules[3].setPosition( GameContext::getWindowRenderer().getSize().x/7, 
                               GameContext::getWindowRenderer().getSize().y/5 + 150.f);

    mGameRules[4].setString("    5. The game's background music can be turned off/on by pressing Y key.");
    mGameRules[4].setOrigin( mGameRules[0].getLocalBounds().width/10, 
                             mGameRules[0].getLocalBounds().height/10);
    mGameRules[4].setPosition( GameContext::getWindowRenderer().getSize().x/7, 
                               GameContext::getWindowRenderer().getSize().y/5 + 250.f);

    const char *s5 = "    6. Once in a while a candy is spawned instead of an apple. There will be maximum 3.\n \
        You win the game if you grab them all.";
    mGameRules[5].setString(std::string(s5));
    mGameRules[5].setOrigin( mGameRules[0].getLocalBounds().width/10, 
                             mGameRules[0].getLocalBounds().height/10);
    mGameRules[5].setPosition( GameContext::getWindowRenderer().getSize().x/7, 
                               GameContext::getWindowRenderer().getSize().y/5 + 300.f);

    mBackButton.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mBackButton.setString("Back");
    mBackButton.setOrigin(  mBackButton.getLocalBounds().width/2, 
                            mBackButton.getLocalBounds().height/2);
    mBackButton.setPosition( GameContext::getWindowRenderer().getSize().x/2, 
                             GameContext::getWindowRenderer().getSize().y/2 + 200.f);
    mBackButton.setCharacterSize(50);
    mBackButton.setFillColor(sf::Color::White);

};

void GameRulesState::processInput()
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
                case sf::Keyboard::Backspace:
                case sf::Keyboard::B:
                {
                    //remove current Game rules state and go back to the previous state (play)
                    GameContext::getStatesManager().popCurrentState();
                }
                break;
                case sf::Keyboard::Up:
                {
                    if(!mIsBackButtonSelected)
                    {
                        mIsBackButtonSelected = true;
                    }
                    else
                    {
                        mIsBackButtonSelected = false;
                    }
                }
                break;
                case sf::Keyboard::Down:
                {
                    if(!mIsBackButtonSelected)
                    {
                        mIsBackButtonSelected = true;
                    }
                    else
                    {
                        mIsBackButtonSelected = false;
                    }
                }
                break;
                case sf::Keyboard::Return:
                {
                    mIsBackButtonPressed = false;

                    if(mIsBackButtonSelected)
                    {
                        mIsBackButtonPressed = true;
                    }
                }
                break;
                default:
                    break;
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Left)
        {
            // Mouse position relative to the window
            auto mouse_pos = sf::Mouse::getPosition(GameContext::getWindowRenderer()); 
            // Mouse position translated into world coordinates
            auto translated_pos = GameContext::getWindowRenderer().mapPixelToCoords(mouse_pos); 

            if (event.type == sf::Event::MouseButtonPressed)
            {
                //left mouse button clicked on Play button and play button wa snot selected before
                if(mBackButton.getGlobalBounds().contains(translated_pos) &&
                    !mIsBackButtonSelected)
                {
                    mIsBackButtonSelected = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if(mBackButton.getGlobalBounds().contains(translated_pos) ||
                    mBackButton.getGlobalBounds().contains(translated_pos))
                {
                    mIsBackButtonPressed = false;

                    if(mIsBackButtonSelected)
                    {
                        mIsBackButtonPressed = true;
                    }
                }
            }
        }
    }
};

void GameRulesState::updateState(sf::Time elapsedTimeSinceLastUpdate)
{
    if(mIsBackButtonSelected)
    {
        mBackButton.setFillColor(sf::Color::Yellow);
    }

    if(mIsBackButtonPressed)
    {
        //remove current Game rules state and go back to the previous state (play)
        GameContext::getStatesManager().popCurrentState();
    }
};

void GameRulesState::drawState()
{
    GameContext::getWindowRenderer().draw(mBackground);

    for(size_t idx{0}; idx < mGameRules.size(); ++idx)
    {
        GameContext::getWindowRenderer().draw(mGameRules[idx]);
    }

    GameContext::getWindowRenderer().draw(mBackButton);

    GameContext::getWindowRenderer().display();
};