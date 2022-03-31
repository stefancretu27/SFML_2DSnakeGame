#pragma once

#include "State.hpp"

#include <stack>
#include <memory>

namespace GenericGameEngine
{
    class StateManager
    {
        public:
            StateManager();
            ~StateManager() = default;

            StateManager(const StateManager&) = delete;
            StateManager& operator=(const StateManager&) = delete;

            // set mNewState member and mark there is a new state to be added to the stack
            void addState(std::unique_ptr<State> NewState, bool replace = false, std::string messagePassedToTheNewState = "");

            // set addRemove to true
            void popCurrentState();

            /*
            * Is the only processing methods, the above 2 just set some variable required by processing. So, they are 
            * called in pairs.
            * It adds mNewState to stack, if mAddState is true. Remove last state in stack (top) if mRemove is true.
            * */
            void processStateChange();

            // return the last state in stack (top)
            std::unique_ptr<State>& getCurrentState();

        private:
            /*
            * Each state is unique and is a consequence of a received input. 
            * Thus, the last input (its state) is the first to be processed.
            */
            std::stack<std::unique_ptr<State>> mStateStack;

            /*
            * When is intended to go to a new state, it is not added directly to the stack.
            * Instead, it is stored separately as it is going to be added to the stack when 
            * the current executing state has finished its processing.
            */
            std::unique_ptr<State> mNewState;

            bool mAddState;
            bool mReplaceState;
            bool mRemoveState;
    };
}