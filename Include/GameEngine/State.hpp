#pragma once

#include <SFML/System/Time.hpp>

#include <string>

namespace GenericGameEngine
{
    //interface for implementing state, used for processing inputs such as: start game, pause game, restart game, close game
    class State
    {
        public:
            State() = default;
            virtual ~State() = default;

            virtual void initState() = 0;
            virtual void processInput() = 0;
            //get called in while(true)
            virtual void updateState(sf::Time elapsedTimeSinceLastUpdate) = 0;
            virtual void drawState() = 0;

            std::string mMessage;
    };
}