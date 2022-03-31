#include "Snake.hpp"
#include "GameContext.hpp"
#include <iostream>

Snake::Snake(): mSnakeBody{std::list<sf::Sprite>(4)}
{
    mSnakeHead = --mSnakeBody.end();
    mSnakeTail = mSnakeBody.begin();
}

void Snake::initSnake(const sf::Texture& texture, float snakeTextureSize)
{
    //save args values in data members, so they can be reused by other methods
    mSnakeTextureSize = snakeTextureSize;
    mSnakeTexture = texture;

    float snakeXTextureSize{mSnakeTextureSize};

    for(auto& snakePart : mSnakeBody)
    {
        //next texture will be displayed on the same Y, but moved on X axis by one texture's size
        snakePart.setTexture(mSnakeTexture);
        snakePart.setPosition({snakeXTextureSize, 4*mSnakeTextureSize});
        snakeXTextureSize += mSnakeTextureSize;
    }
}

void Snake::moveSnake(const sf::Vector2f& direction)
{
    /*
    * Do not move the entire snake's body, just only move the element pointed to by the tail iterator, next to the head. That said, 
    * using head's actual position and the arg direction, whose abs value equals a body part size, the last's element position is changed,
    * being placed next to the head. Hence, a movement illusion is created, as every frame, the last body part becomes the new first.
    * */
    mSnakeTail->setPosition(mSnakeHead->getPosition() + direction);
    // Set the head iterator to point to the new body part that is rendered the first in the list
    mSnakeHead = mSnakeTail;
    // Update tail iterator such that it points to the next element in list (the second to last one), which would become the new tail (last one)
    ++mSnakeTail;

    // if tail iterator reached out the end of the list, reset it to be the new begin
    if(mSnakeTail == mSnakeBody.end())
    {
        mSnakeTail = mSnakeBody.begin();
    }
}

bool Snake::hasSnakeCollidedWithObject(const sf::Sprite& otherObject) const
{
    return otherObject.getGlobalBounds().intersects(mSnakeHead->getGlobalBounds());
}

bool Snake::hasSnakeCollidedWithSelf()
{
    bool result{false};

    for(std::list<sf::Sprite>::iterator it{mSnakeHead}, end{mSnakeBody.end()}; it != end; ++it)
    {
        if(it != mSnakeHead && hasSnakeCollidedWithObject(*it))
        {
            result  = true;
            break;
        }
    }

    return result;
}

void Snake::growSnake(const sf::Vector2f& direction)
{
    //build new body part specifying the texture amd set its position in the same direction, next to the head
    sf::Sprite newSnakeBodyPart{mSnakeTexture};
    newSnakeBodyPart.setPosition(mSnakeHead->getPosition() + direction);

    // as the new value is inserted at the end of the list, insert returns iterator to it, which is used to set position of the new head
    mSnakeHead = mSnakeBody.insert(++mSnakeHead, newSnakeBodyPart);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    for(auto& snakePart : mSnakeBody)
    {
        target.draw(snakePart);
    }
}