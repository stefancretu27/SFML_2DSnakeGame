#include "GameOverState.hpp"
#include "GamePlayState.hpp"

#include <SFML/Window/Event.hpp>

GameOverState::GameOverState(): mIsReplayButtonSelected{true},
                                mIsReplayButtonPressed{false},
                                mIsExitButtonSelected{false},
                                mIsExitButtonPressed{false}
{}

void GameOverState::initState()
{
    // set the texture source of the Sprite object using as argument the corresponding texture loaded in GameContext's assets
    mBackground.setTexture(GameContext::getAssetsManager().getTexture(GameContext::MainMenuBackground));
    /*
    * Set the subrectangle of the texture that the Sprite will display. Useful for displaying a part of the texture, not the whole,
    * but the default setting displays the entire texture. The argument is an IntRect objects which takes 4 parameters: the first
    * 2 are coordinates of the top left corner of the rectangle, the next two are wifth and height of the rectangle.
    * 
    * Viewport takes as argument an sf::View, which is used to display a specific part of the whole scene.
    * If no view is set, the view is set to the entire window, which is specified by DefaultView.
    */
    mBackground.setTextureRect(GameContext::getWindowRenderer().getViewport(GameContext::getWindowRenderer().getDefaultView()));

    // Game title
    mGameOverTitle.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mGameOverTitle.setString("Game over! :(");
    /*
    * The origin of an object defines the center point of all its transformations: position, scale or rotation.
    * The coordinates of this point denote the center of the object are are relative to the top left corner, which is
    * the origin of the window's coordinates system.
    */
    mGameOverTitle.setOrigin( mGameOverTitle.getLocalBounds().width/2, 
                              mGameOverTitle.getLocalBounds().height/2);
    /*
    * For a text object, it is possible to set its position on the window, so change it with respect to the window's size,
    * such that the text will be more centered. Nonetheless, it would be displayed starting with the center of the window, 
    * not in the window's center. This aspect is mitigated by setting its origin. 
    * */
    mGameOverTitle.setPosition( GameContext::getWindowRenderer().getSize().x/2 - 60.f, 
                                GameContext::getWindowRenderer().getSize().y/2 - 250.f);
    mGameOverTitle.setCharacterSize(80);
    mGameOverTitle.setFillColor(sf::Color::Red);

    // Game over message
    mGameOverMessage.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mGameOverMessage.setString(mMessage);
    mGameOverMessage.setOrigin( mGameOverMessage.getLocalBounds().width/2, 
                                mGameOverMessage.getLocalBounds().height/2);
    mGameOverMessage.setPosition( GameContext::getWindowRenderer().getSize().x/2 - 80.f, 
                                GameContext::getWindowRenderer().getSize().y/2 - 150.f);
    mGameOverMessage.setCharacterSize(50);
    mGameOverMessage.setFillColor(sf::Color::Black);


    //Play button
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
};

void GameOverState::processInput()
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

void GameOverState::updateState(sf::Time elapsedTimeSinceLastUpdate)
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
        GameContext::getStatesManager().addState(std::make_unique<GamePlayState>(), true);
    }
    else if(mIsExitButtonPressed)
    {
        GameContext::getWindowRenderer().close();
    }
};

void GameOverState::drawState()
{
    GameContext::getWindowRenderer().clear();
    GameContext::getWindowRenderer().draw(mBackground);
    GameContext::getWindowRenderer().draw(mGameOverTitle);
    GameContext::getWindowRenderer().draw(mGameOverMessage);
    GameContext::getWindowRenderer().draw(mReplayButton);
    GameContext::getWindowRenderer().draw(mExitButton);
    GameContext::getWindowRenderer().display();
};