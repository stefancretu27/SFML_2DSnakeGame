#include "GamePlayState.hpp"
#include "GameOverState.hpp"
#include "GamePausedState.hpp"
#include "GameWonState.hpp"

#include <SFML/Window/Event.hpp>

#include <cstdlib>
#include <ctime>

#include <iostream>

GamePlayState::GamePlayState(): mElapsedTime{sf::Time::Zero}
{
    srand(time(nullptr));
}

bool GamePlayState::drawCandy()
{
    return mScore != 0 && mScore < 20 &&                 //do not enable candy at the first frame
            mCandyScore < 3 &&                          //enable candy maximum 3 times
                mScore%4 == 0 ;                         //enable candy when 4 divides the score
}

void GamePlayState::initState()
{
    /* 
    * Load textures to the assets collection in the current context, as they must exists in the program, as long as Sprite objects use them.
    * This is necessary as the Sprite does not store the texture itself, but keeps a pointer to the passed argument.
    */
    GameContext::getAssetsManager().addTexture(GameContext::Grass, 
                                                "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Textures\\gameGrassBackground_219x230.jpg", true);
    GameContext::getAssetsManager().addTexture(GameContext::Food, 
                                                "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Textures\\Apple_24p.png");
    GameContext::getAssetsManager().addTexture(GameContext::Wall, 
                                                "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Textures\\brickWall_32p.jpg", true);
    GameContext::getAssetsManager().addTexture(GameContext::SnakeBody, 
                                                "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Textures\\c++SnakeBodyPart_24p.png");
    GameContext::getAssetsManager().addTexture(GameContext::Candy, 
                                                "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Textures\\purpleCandy_52x24p.png");
    /* 
    * Load sound buffer to the assets collection in the current context, as they must exists in the program, as long as Sound objects use them.
    * This is necessary as the Sound does not store the texture sound stream, but keeps a pointer to the passed argument. Sounds and music
    * are played in a different thread, therefore, after play() call is commenced, the execution of the current thread continues, without
    * waiting for play() call to end. The default volume os a sound is 100, that is maximum.
    * 
    * The SoundBuffer class lass encapsulates the audio data, which is an array of 16-bit signed integers, called "audio samples". 
    * A sample is the amplitude of the sound signal at a given point in time, and an array of samples therefore represents a full sound. 
    * https://www.sfml-dev.org/tutorials/2.5/audio-sounds.php
    */
    GameContext::getAssetsManager().addSoundBuffer(GameContext::AppleBiteSound, 
                                                    "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Sounds\\appleBiteSoundEffect.wav");
    GameContext::getAssetsManager().addSoundBuffer(GameContext::SnakeStrikeSound, 
                                                    "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Sounds\\snakeStrikeSound.ogg");
    GameContext::getAssetsManager().addSoundBuffer(GameContext::SnakeRattlingSound, 
                                                    "C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Sounds\\snakeRattlingSound.ogg");

    // Grass
    mGrass.setTexture(GameContext::getAssetsManager().getTexture(GameContext::Grass));
    mGrass.setTextureRect(GameContext::getWindowRenderer().getViewport(GameContext::getWindowRenderer().getDefaultView()));

    // Walls
    for(auto& wall : mWalls)
    {
        wall.setTexture(GameContext::getAssetsManager().getTexture(GameContext::Wall));
    }

    // left and right walls display an identical texture, being narrower on x axis
    int xOriginVerticalWallTexture{5}, yOriginVerticalWallTexture{5};
    int widthVerticalWall{20};
    // setTexture Rect has a single parameter, that is an sf::IntRect, which is an alias for sf::Rect<int>
    mWalls[0].setTextureRect(sf::IntRect{ xOriginVerticalWallTexture, 
                                          yOriginVerticalWallTexture,
                                          widthVerticalWall, 
                                          static_cast<int>(GameContext::getWindowRenderer().getSize().y)});
    mWalls[1].setTextureRect(sf::Rect<int>{ xOriginVerticalWallTexture, 
                                            yOriginVerticalWallTexture,
                                            widthVerticalWall, 
                                            static_cast<int>(GameContext::getWindowRenderer().getSize().y)});
    // explicitly set the right wall's position 
    mWalls[1].setPosition(GameContext::getWindowRenderer().getSize().x - widthVerticalWall, 0);

    // up and down walls display an identical texture, being narrower on y axis
    int xOriginHorizontalWallTexture{0}, yOriginHorizontalWallTexture{0};
    int heightHorizontalWall{24};
    mWalls[2].setTextureRect(sf::IntRect{ xOriginHorizontalWallTexture, 
                                          yOriginHorizontalWallTexture,
                                          static_cast<int>(GameContext::getWindowRenderer().getSize().x), 
                                          heightHorizontalWall});
    mWalls[3].setTextureRect(sf::IntRect{ xOriginHorizontalWallTexture, 
                                          yOriginHorizontalWallTexture,
                                          static_cast<int>(GameContext::getWindowRenderer().getSize().x), 
                                          heightHorizontalWall});
    // explicitly set the down wall's position 
    mWalls[3].setPosition(0, GameContext::getWindowRenderer().getSize().y - heightHorizontalWall);

    // Food & candy
    mFood.setTexture(GameContext::getAssetsManager().getTexture(GameContext::Food));
    mFood.setPosition( GameContext::getWindowRenderer().getSize().x/2, 
                       GameContext::getWindowRenderer().getSize().y/2 );

    // Snake
    auto snakeTexture{GameContext::getAssetsManager().getTexture(GameContext::SnakeBody)};
    mSnakeTextureSize = snakeTexture.getSize().x;
    mSnakeDirection = {mSnakeTextureSize, 0.f};
    mSnake.initSnake(snakeTexture, mSnakeTextureSize);

    mScoreText.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mScoreText.setPosition(2*mSnakeTextureSize, 0.f);
    mScoreText.setString("Score : " + std::to_string(mScore));
    mScoreText.setCharacterSize(25);
    mScoreText.setFillColor(sf::Color::White);

    mCandy.setTexture(GameContext::getAssetsManager().getTexture(GameContext::Candy));
    mCandy.setPosition( mCandy.getTexture()->getSize().x/2, 
                        mCandy.getTexture()->getSize().y);

    mCandyScoreText.setFont(GameContext::getAssetsManager().getFont(GameContext::MainFont));
    mCandyScoreText.setPosition(GameContext::getWindowRenderer().getSize().x - 2*mCandy.getTexture()->getSize().x, 0.f);
    mCandyScoreText.setString("Candy : " + std::to_string(mCandyScore));
    mCandyScoreText.setCharacterSize(25);
    mCandyScoreText.setFillColor(sf::Color::Yellow);

    //set buffers and volumes for game sounds
    mAppleBiteSound.setBuffer(GameContext::getAssetsManager().getSoundBuffer(GameContext::AppleBiteSound));
    mAppleBiteSound.setVolume(mDefaultMusicVolume);
    mSnakeStrike.setBuffer(GameContext::getAssetsManager().getSoundBuffer(GameContext::SnakeStrikeSound));
    mSnakeStrike.setVolume(mDefaultMusicVolume);
    mSnakeRattling.setBuffer(GameContext::getAssetsManager().getSoundBuffer(GameContext::SnakeRattlingSound));
    mSnakeRattling.setVolume(mDefaultMusicVolume);

    //start background music
    if(mBackgroundMusic.openFromFile("C:\\Users\\scretu\\VisualCodeProjects\\Snake_game\\Assets\\Sounds\\gameBackgroundMusic.ogg"))
    {
        mBackgroundMusic.setVolume(mDefaultMusicVolume);
        mBackgroundMusic.play();
        //play background music repeatedly
        mBackgroundMusic.setLoop(true);
    }
}

void GamePlayState::processInput()
{
    if(isMusicPaused && mBackgroundMusic.getStatus() == sf::SoundSource::Paused)
    {
        mBackgroundMusic.play();
        isMusicPaused = false;
    }

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
        else if(event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection{mSnakeDirection};

            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    newDirection = {0.f, -mSnakeTextureSize};
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    newDirection = {0.f, mSnakeTextureSize};
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    newDirection = {-mSnakeTextureSize, 0.f};
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    newDirection = {mSnakeTextureSize, 0.f};
                    break;
                case sf::Keyboard::Escape:
                case sf::Keyboard::P:
                {
                    if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
                    {
                        isMusicPaused = true;
                        mBackgroundMusic.pause();
                    }

                    GameContext::getStatesManager().addState(std::make_unique<GamePausedState>());
                }
                    break;
                case sf::Keyboard::Y:
                { 
                    if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
                    {
                        mBackgroundMusic.pause();
                    }
                    else if(mBackgroundMusic.getStatus() == sf::SoundSource::Paused)
                    {
                        mBackgroundMusic.play();
                    }
                }
                    break;
                default:
                    break;
            }

            // check if the new direction is not the opposite of the existing direction (up vs down or left vs right should not be allowed)
            if( std::abs(mSnakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(mSnakeDirection.y) != std::abs(newDirection.y) )
            {
                mSnakeDirection = newDirection;
            }
        }
    }
}

void GamePlayState::updateState(sf::Time elapsedTimeSinceLastUpdate)
{
    mElapsedTime += elapsedTimeSinceLastUpdate;

    if(mElapsedTime.asSeconds() > 0.2)
    {
        // if the snake collides with wall it is a game over
        for( auto& wall : mWalls)
        {
            if(mSnake.hasSnakeCollidedWithObject(wall))
            {
                //stop background music and play snake rattling sound before moving to game over state
                if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
                {
                    mBackgroundMusic.stop();
                }
                mSnakeRattling.play();

                GameContext::getStatesManager().addState(std::make_unique<GameOverState>(), true, "The snake couldn't digest that brick wall!");
                break;
            }
        }

        if(mSnake.hasSnakeCollidedWithSelf())
        {
            //stop background music and play snake rattling sound before moving to game over state
            if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
            {
                mBackgroundMusic.stop();
            }
            mSnakeRattling.play();

            GameContext::getStatesManager().addState(std::make_unique<GameOverState>(), true, "The snake did not like its tail's taste!");
        }

        if(mCandyScore == 1)
        {
            //stop background music before moving to game won state
            if(mBackgroundMusic.getStatus() == sf::SoundSource::Playing)
            {
                mBackgroundMusic.stop();
            }

            GameContext::getStatesManager().addState(std::make_unique<GameWonState>(), true);
        }

        //do not move the snake if it is growing, as growth can be perceived as a movement by one piece
        if(!isDrawCandyEnabled && mSnake.hasSnakeCollidedWithObject(mFood))
        {
            //play apple bite sound
            mAppleBiteSound.play();

            isDrawCandyEnabled = false;
            mSnake.growSnake(mSnakeDirection);

            // get a random x position within the bounds of window's width, taking into account walls' width which equal snake texture size
            int foodXPos = std::clamp<int>( rand() % GameContext::getWindowRenderer().getSize().x,                  //value to be clamped
                                            mSnakeTextureSize,                                                      // min threshold                    
                                            GameContext::getWindowRenderer().getSize().x - 2*mSnakeTextureSize);    // max threshold
            int foodYPos = std::clamp<int>( rand() % GameContext::getWindowRenderer().getSize().y, 
                                            mSnakeTextureSize,
                                            GameContext::getWindowRenderer().getSize().y - 2*mSnakeTextureSize);

            mFood.setPosition(foodXPos, foodYPos);

            ++mScore;
            
            mScoreText.setString("Score : " + std::to_string(mScore));
            mScoreText.setPosition(2*mSnakeTextureSize, 0.f);
            mScoreText.setCharacterSize(25);
            mScoreText.setFillColor(sf::Color::White);

            mCandyScoreText.setString("Candy : " + std::to_string(mCandyScore));
            mCandyScoreText.setPosition(GameContext::getWindowRenderer().getSize().x - 2*mCandy.getTexture()->getSize().x, 0.f);
            mCandyScoreText.setCharacterSize(25);
            mCandyScoreText.setFillColor(sf::Color::Yellow);
        }
        else if (isDrawCandyEnabled && mSnake.hasSnakeCollidedWithObject(mCandy))
        {
            //play snake strike sound when eating a candy
            mSnakeStrike.play();

            isDrawCandyEnabled = false;
            // the snake and the score grow by 2 tiles/points, instead of only one
            mSnake.growSnake(mSnakeDirection);
            mSnake.growSnake(mSnakeDirection);

            // get a random x position within the bounds of window's width, taking into account walls' width which equal snake texture size
            int candyXPos = std::clamp<int>( rand() % GameContext::getWindowRenderer().getSize().x,                 
                                             mSnakeTextureSize+mSnakeTextureSize,
                                             GameContext::getWindowRenderer().getSize().x - 3*mSnakeTextureSize);
            int candyYPos = std::clamp<int>( rand() % GameContext::getWindowRenderer().getSize().y, 
                                             mSnakeTextureSize,
                                             GameContext::getWindowRenderer().getSize().y - 2*mSnakeTextureSize);

            mCandy.setPosition(candyXPos, candyYPos);

            mScore += 2;

            mScoreText.setString("Score : " + std::to_string(mScore));
            mScoreText.setPosition(2*mSnakeTextureSize, 0.f);
            mScoreText.setCharacterSize(25);
            mScoreText.setFillColor(sf::Color::White);

            ++mCandyScore;

            mCandyScoreText.setString("Candy : " + std::to_string(mCandyScore));
            mCandyScoreText.setPosition(GameContext::getWindowRenderer().getSize().x - 2*mCandy.getTexture()->getSize().x, 0.f);
            mCandyScoreText.setCharacterSize(25);
            mCandyScoreText.setFillColor(sf::Color::Yellow);   
        }
        else
        {
            mSnake.moveSnake(mSnakeDirection);
        }

        mElapsedTime = sf::Time::Zero;
    }
}

void GamePlayState::drawState()
{
    //clear what is rendered by previous state
    GameContext::getWindowRenderer().clear();

    //render assets particular to the current state
    GameContext::getWindowRenderer().draw(mGrass);
    for(auto& wall : mWalls)
    {
        GameContext::getWindowRenderer().draw(wall);
    }

    if(drawCandy())
    {
        isDrawCandyEnabled = true;
        GameContext::getWindowRenderer().draw(mCandy);
    }
    else
    {
        GameContext::getWindowRenderer().draw(mFood);
    }

    GameContext::getWindowRenderer().draw(mSnake);
    GameContext::getWindowRenderer().draw(mScoreText);
    GameContext::getWindowRenderer().draw(mCandyScoreText);

    // display assets of the current state
    GameContext::getWindowRenderer().display();
}

