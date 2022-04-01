#include "GameWonState.hpp"
#include "GameContext.hpp"
#include "GamePlayState.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>

GameWonState::GameWonState(): mIsReplayButtonSelected{true},
                                mIsReplayButtonPressed{false},
                                mIsExitButtonSelected{false},
                                mIsExitButtonPressed{false}
{}

void GameWonState::initState()
{
     // set the texture source of the Sprite object using as argument the corresponding texture loaded in GameContext's assets
    mBackground.setTexture(GameContext::getAssetsManager().getTexture(GameContext::MainMenuBackground));
    mBackground.setTextureRect(GameContext::getWindowRenderer().getViewport(GameContext::getWindowRenderer().getDefaultView()));

    // Game Win title
    mWinTitle.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mWinTitle.setString("Congrats!You took all 3 candies!");

    mWinTitle.setOrigin( mWinTitle.getLocalBounds().width/2, 
                         mWinTitle.getLocalBounds().height/2);
    mWinTitle.setPosition( GameContext::getWindowRenderer().getSize().x/2 - 150.f, 
                           GameContext::getWindowRenderer().getSize().y/2 - 250.f);

    mWinTitle.setCharacterSize(80);
    mWinTitle.setFillColor(sf::Color::Cyan);

    //Replay button
    mReplayButton.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mReplayButton.setString("Replay");
    mReplayButton.setOrigin(  mReplayButton.getLocalBounds().width/2, 
                              mReplayButton.getLocalBounds().height/2);
    mReplayButton.setPosition( GameContext::getWindowRenderer().getSize().x/2, 
                               GameContext::getWindowRenderer().getSize().y/2 - 30.f);
    mReplayButton.setCharacterSize(50);
    mReplayButton.setFillColor(sf::Color::White);


    //Exit button
    mExitButton.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mExitButton.setString("Exit game");
    mExitButton.setOrigin(  mExitButton.getLocalBounds().width/2, 
                            mExitButton.getLocalBounds().height/2);
    mExitButton.setPosition( GameContext::getWindowRenderer().getSize().x/2, 
                             GameContext::getWindowRenderer().getSize().y/2 + 30.f);
    mExitButton.setCharacterSize(50);
    mExitButton.setFillColor(sf::Color::White);

    if(mBackgroundMusic.openFromFile(GameContext::getAssetsPath() + "Sounds\\robbie williams - candy.wav"))
    {
        mBackgroundMusic.setVolume(mDefaultMusicVolume);
        mBackgroundMusic.play();
    }
};

void GameWonState::processInput()
{
    //class Event is defined in Window module and does not have a definition macro directive
    sf::Event event;
    while (GameContext::getWindowRenderer().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
            {
                mBackgroundMusic.stop();
            }
            GameContext::getWindowRenderer().close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // event.key.code stores the key that was lastly pressed
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    if(!mIsReplayButtonSelected)
                    {
                        mIsReplayButtonSelected = true;
                        mIsExitButtonSelected = false;
                    }
                }
                break;

                case sf::Keyboard::Down:
                {
                    if(!mIsExitButtonSelected)
                    {
                        mIsReplayButtonSelected = false;
                        mIsExitButtonSelected = true;
                    }
                }
                break;

                case sf::Keyboard::Return:
                {
                    mIsReplayButtonPressed = false;
                    mIsExitButtonPressed = false;

                    if(mIsReplayButtonSelected)
                    {
                        mIsReplayButtonPressed = true;
                    }
                    else
                    {
                        mIsExitButtonPressed = true;
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
                if(mReplayButton.getGlobalBounds().contains(translated_pos) &&
                    !mIsReplayButtonSelected)
                {
                    mIsReplayButtonSelected = true;
                    mIsExitButtonSelected = false;
                }
                //left mouse button clicked on Exit button and play button wa snot selected before
                else if(mExitButton.getGlobalBounds().contains(translated_pos) &&
                        !mIsExitButtonSelected)
                {
                    mIsReplayButtonSelected = false;
                    mIsExitButtonSelected = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if(mReplayButton.getGlobalBounds().contains(translated_pos) ||
                    mExitButton.getGlobalBounds().contains(translated_pos))
                {
                    mIsReplayButtonPressed = false;
                    mIsExitButtonPressed = false;

                    if(mIsReplayButtonSelected)
                    {
                        mIsReplayButtonPressed = true;
                    }
                    else
                    {
                        mIsExitButtonPressed = true;
                    }
                }
            }
        }
    }
};

void GameWonState::updateState(sf::Time elapsedTimeSinceLastUpdate)
{
    if(mIsReplayButtonSelected)
    {
        mReplayButton.setFillColor(sf::Color::Yellow);
        mExitButton.setFillColor(sf::Color::White);
    }
    else if(mIsExitButtonSelected)
    {
        mReplayButton.setFillColor(sf::Color::White);
        mExitButton.setFillColor(sf::Color::Yellow);
    }

    if(mIsReplayButtonPressed)
    {
        if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
        {
            mBackgroundMusic.stop();
        }

        GameContext::getStatesManager().addState(std::make_unique<GamePlayState>(), true);
    }
    else if(mIsExitButtonPressed)
    {
        if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
        {
            mBackgroundMusic.stop();
        }

        GameContext::getWindowRenderer().close();
    }
};

void GameWonState::drawState()
{
    GameContext::getWindowRenderer().clear();
    GameContext::getWindowRenderer().draw(mBackground);
    GameContext::getWindowRenderer().draw(mWinTitle);
    GameContext::getWindowRenderer().draw(mReplayButton);
    GameContext::getWindowRenderer().draw(mExitButton);
    GameContext::getWindowRenderer().display();
};