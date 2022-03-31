#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <list>

class Snake : public sf::Drawable
{
    public:
        Snake();
        ~Snake() = default;

        // initialize the snake object with the given texture
        void initSnake(const sf::Texture& texture, float snakeTextureSize);
        // move the snake in the given direction
        void moveSnake(const sf::Vector2f& direction);
        bool hasSnakeCollidedWithObject(const sf::Sprite& otherObject) const;
        bool hasSnakeCollidedWithSelf();
        // grow the snake in the given direction
        void growSnake(const sf::Vector2f& direction);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Texture mSnakeTexture;
        float mSnakeTextureSize{};
        std::list<sf::Sprite> mSnakeBody;
        std::list<sf::Sprite>::iterator mSnakeTail;
        std::list<sf::Sprite>::iterator mSnakeHead;
};