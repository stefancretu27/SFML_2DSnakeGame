#include "MainMenuState.hpp"
#include "GamePlayState.hpp"
#include "GameRulesState.hpp"

#include <SFML/Window/Event.hpp>

MainMenuState::MainMenuState(): mIsPlayButtonSelected{true},
                                mIsPlayButtonPressed{false},
                                mIsExitButtonSelected{false},
                                mIsExitButtonPressed{false},
                                mIsGameRulesButtonSelected{false},
                                mIsGameRulesButtonPressed{false}
{}

void MainMenuState::initState()
{
    /* 
    * Main menu Background
    *
    * Load texture to the assets collection in the current context, as they must exists in the program, as long as Sprite objects use them.
    * This is necessary as the Sprite does not store the texture itself, but keeps a pointer to the passed argument.
    */
    GameContext::getAssetsManager().addTexture(GameContext::MainMenuBackground, 
                                                GameContext::getAssetsPath() + "Textures\\grassBackground_225p.jpg", true);
    
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


    /*
    * Buttons
    *
    * Load fonts to the assets collection in the current context, which is used subsequently for all Text objects.
    * As in the case of Sprite, the fonts must exist in the program, as long as Text objects use them.
    * This is necessary as the Text does not store the texture itself, but keeps a pointer to the passed argument.
    * 
    * Fonts source: https://fonts.google.com/
    * */
    GameContext::getAssetsManager().addFont(GameContext::MainFont, 
                                            GameContext::getAssetsPath() + "Fonts\\League_Gothic\\LeagueGothic-Regular-VariableFont_wdth.ttf");
    

    // Game title
    mGameTitle.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mGameTitle.setString("Snake Game");
    /*
    * The origin of an object defines the center point of all its transformations: position, scale or rotation.
    * The coordinates of this point denote the center of the object are are relative to the top left corner, which is
    * the origin of the window's coordinates system.
    */
    mGameTitle.setOrigin( mGameTitle.getLocalBounds().width/2, 
                          mGameTitle.getLocalBounds().height/2);
    /*
    * For a text object, it is possible to set its position on the window, so change it with respect to the window's size,
    * such that the text will be more centered. Nonetheless, it would be displayed starting with the center of the window, 
    * not in the window's center. This aspect is mitigated by setting its origin. 
    * */
    mGameTitle.setPosition( GameContext::getWindowRenderer().getSize().x/2 - 30.f, 
                            GameContext::getWindowRenderer().getSize().y/5);
    mGameTitle.setCharacterSize(110);
    mGameTitle.setFillColor(sf::Color::Cyan);


    //Play button
    mPlayButton.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mPlayButton.setString("Play");
    mPlayButton.setOrigin(  mPlayButton.getLocalBounds().width/2, 
                            mPlayButton.getLocalBounds().height/2);
    mPlayButton.setPosition( GameContext::getWindowRenderer().getSize().x/2 + 10.f, 
                             GameContext::getWindowRenderer().getSize().y/2 - 30.f);
    mPlayButton.setCharacterSize(50);
    mPlayButton.setFillColor(sf::Color::White);

    //Exit button
    mExitButton.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mExitButton.setString("Exit game");
    mExitButton.setOrigin(  mExitButton.getLocalBounds().width/2, 
                            mExitButton.getLocalBounds().height/2);
    mExitButton.setPosition( GameContext::getWindowRenderer().getSize().x/2, 
                             GameContext::getWindowRenderer().getSize().y/2 + 30.f);
    mExitButton.setCharacterSize(50);
    mExitButton.setFillColor(sf::Color::White);

    //Game rules
    mGameRulesButton.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mGameRulesButton.setString("Game rules");
    mGameRulesButton.setOrigin(  mGameRulesButton.getLocalBounds().width/2, 
                            mGameRulesButton.getLocalBounds().height/2);
    mGameRulesButton.setPosition( GameContext::getWindowRenderer().getSize().x/2 - 10.f, 
                             GameContext::getWindowRenderer().getSize().y/2 + 90.f);
    mGameRulesButton.setCharacterSize(50);
    mGameRulesButton.setFillColor(sf::Color::White);


    // c++ logo built out of c++logo icons
    GameContext::getAssetsManager().addTexture(GameContext::LogoIcon, 
                                                GameContext::getAssetsPath() + "Textures\\c++SnakeBodyPart_24p.png");

    //Set powsition for mini logos that compose the C++ logo
    mLogoPieceTexture = GameContext::getAssetsManager().getTexture(GameContext::LogoIcon);
    mSnakeTextureSize = 24.f;
    float logoTextureSize{mSnakeTextureSize};
    
    // the C part of the logo : top line
    for(size_t idx{0}; idx < 4; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/5.2 + logoTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5);
        logoTextureSize += mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }

    // the C part of the logo : side line
    //reset logo size indexer
    logoTextureSize = mSnakeTextureSize;

    for(size_t idx{0}; idx < 3; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/5.2 + mSnakeTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5 + logoTextureSize);
        logoTextureSize += mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }

    // the C part of the logo : top line
    //reset logo size indexer
    logoTextureSize = mSnakeTextureSize;

    for(size_t idx{0}; idx < 4; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/5.2 + logoTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5 + 4*mSnakeTextureSize);
        logoTextureSize += mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }

    // the ++ part of the logo : horizontal lines
    //reset logo size indexer
    logoTextureSize = mSnakeTextureSize;

    for(size_t idx{0}; idx < 3; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/3.7 + logoTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5 + 2*mSnakeTextureSize);
        logoTextureSize += mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }

    //reset logo size indexer
    logoTextureSize = mSnakeTextureSize;

    for(size_t idx{0}; idx < 3; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/3 + logoTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5 + 2*mSnakeTextureSize);
        logoTextureSize += mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }

    // the ++ part of the logo : vertical lines
    //reset logo size indexer
    logoTextureSize = mSnakeTextureSize;

    for(size_t idx{0}; idx < 2; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/3.7 + 2*mSnakeTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5 + logoTextureSize);
        logoTextureSize += 2*mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }

    //reset logo size indexer
    logoTextureSize = mSnakeTextureSize;

    for(size_t idx{0}; idx < 2; ++idx)
    {
        sf::Sprite logoPiece;
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        logoPiece.setTexture(mLogoPieceTexture);
        logoPiece.setPosition( GameContext::getWindowRenderer().getSize().x/3 + 2*mSnakeTextureSize, 
                               GameContext::getWindowRenderer().getSize().y/5 + logoTextureSize);
        logoTextureSize += 2*mSnakeTextureSize;

        mLogo.push_back(logoPiece);
    }
};

void MainMenuState::processInput()
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
                    if(!mIsExitButtonSelected && mIsGameRulesButtonSelected)
                    {
                        mIsPlayButtonSelected = false;
                        mIsExitButtonSelected = true;
                        mIsGameRulesButtonSelected = false;
                    }
                    else if(!mIsPlayButtonSelected && mIsExitButtonSelected)
                    {
                        mIsPlayButtonSelected = true;
                        mIsExitButtonSelected = false;
                        mIsGameRulesButtonSelected = false;
                    }
                }
                break;

                case sf::Keyboard::Down:
                {
                    if(!mIsExitButtonSelected && !mIsGameRulesButtonSelected)
                    {
                        mIsPlayButtonSelected = false;
                        mIsExitButtonSelected = true;
                        mIsGameRulesButtonSelected = false;
                    }
                    else if(mIsExitButtonSelected && !mIsGameRulesButtonSelected )
                    {
                        mIsPlayButtonSelected = false;
                        mIsExitButtonSelected = false;
                        mIsGameRulesButtonSelected = true;
                    }
                }
                break;

                case sf::Keyboard::Return:
                {
                    mIsPlayButtonPressed = false;
                    mIsExitButtonPressed = false;
                    mIsGameRulesButtonPressed = false;

                    if(mIsPlayButtonSelected && !mIsExitButtonSelected && !mIsGameRulesButtonSelected)
                    {
                        mIsPlayButtonPressed = true;
                    }
                    else if(mIsExitButtonSelected && !mIsPlayButtonSelected && !mIsGameRulesButtonSelected)
                    {
                        mIsExitButtonPressed = true;
                    }
                    else if(!mIsExitButtonSelected && !mIsPlayButtonSelected && mIsGameRulesButtonSelected)
                    {
                        mIsGameRulesButtonPressed = true;
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
                //left mouse button clicked on Play button and play button was not selected before
                if(mPlayButton.getGlobalBounds().contains(translated_pos) &&
                    !mIsPlayButtonSelected)
                {
                    mIsPlayButtonSelected = true;
                    mIsExitButtonSelected = false;
                    mIsGameRulesButtonSelected = false;
                }
                //left mouse button clicked on Exit button and play button was not selected before
                else if(mExitButton.getGlobalBounds().contains(translated_pos) &&
                        !mIsExitButtonSelected)
                {
                    mIsPlayButtonSelected = false;
                    mIsExitButtonSelected = true;
                    mIsGameRulesButtonSelected = false;
                }
                else if(mGameRulesButton.getGlobalBounds().contains(translated_pos) &&
                        !mIsGameRulesButtonSelected)
                {
                    mIsPlayButtonSelected = false;
                    mIsGameRulesButtonSelected = false;
                    mIsGameRulesButtonSelected = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if(mPlayButton.getGlobalBounds().contains(translated_pos) ||
                    mExitButton.getGlobalBounds().contains(translated_pos) ||
                    mGameRulesButton.getGlobalBounds().contains(translated_pos))
                {
                    mIsPlayButtonPressed = false;
                    mIsExitButtonPressed = false;
                    mIsGameRulesButtonPressed = false;

                    if(mIsPlayButtonSelected && !mIsExitButtonSelected && !mIsGameRulesButtonSelected)
                    {
                        mIsPlayButtonPressed = true;
                    }
                    else if(mIsExitButtonSelected && !mIsPlayButtonSelected && !mIsGameRulesButtonSelected)
                    {
                        mIsExitButtonPressed = true;
                    }
                    else if(!mIsExitButtonSelected && !mIsPlayButtonSelected && mIsGameRulesButtonSelected)
                    {
                        mIsGameRulesButtonPressed = true;
                    }
                }
            }
        }
    }
};

void MainMenuState::updateState(sf::Time elapsedTimeSinceLastUpdate)
{
    if(mIsPlayButtonSelected)
    {
        mPlayButton.setFillColor(sf::Color::Yellow);
        mExitButton.setFillColor(sf::Color::White);
        mGameRulesButton.setFillColor(sf::Color::White);
    }
    else if(mIsExitButtonSelected)
    {
        mPlayButton.setFillColor(sf::Color::White);
        mExitButton.setFillColor(sf::Color::Yellow);
        mGameRulesButton.setFillColor(sf::Color::White);
    }
    else if(mIsGameRulesButtonSelected)
    {
        mPlayButton.setFillColor(sf::Color::White);
        mExitButton.setFillColor(sf::Color::White);
        mGameRulesButton.setFillColor(sf::Color::Yellow);
    }

    if(mIsPlayButtonPressed)
    {
        mIsPlayButtonPressed = false;
        GameContext::getStatesManager().addState(std::make_unique<GamePlayState>(), true);
    }
    else if(mIsExitButtonPressed)
    {
        GameContext::getWindowRenderer().close();
    }
    else if(mIsGameRulesButtonPressed)
    {
        mIsGameRulesButtonPressed = false;
        GameContext::getStatesManager().addState(std::make_unique<GameRulesState>(), true);
    }
};

void MainMenuState::drawState()
{
    GameContext::getWindowRenderer().clear();
    GameContext::getWindowRenderer().draw(mBackground);
    GameContext::getWindowRenderer().draw(mGameTitle);
    GameContext::getWindowRenderer().draw(mPlayButton);
    GameContext::getWindowRenderer().draw(mExitButton);
    GameContext::getWindowRenderer().draw(mGameRulesButton);

    for(auto& logoPiece : mLogo)
    {
        GameContext::getWindowRenderer().draw(logoPiece);
    }

    GameContext::getWindowRenderer().display();
};
