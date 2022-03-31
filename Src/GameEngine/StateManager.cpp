#include "GameEngine/StateManager.hpp"

namespace GenericGameEngine
{
    using namespace std;

    StateManager::StateManager():mAddState{false}, mReplaceState{false}, mRemoveState{false} {};

    // do not redefine default argument in function's definition, as it suffices to be specified in function's declaration
    void StateManager::addState(std::unique_ptr<State> NewState, bool replace, std::string messagePassedToTheNewState)
    {
        mAddState = true;
        mNewState = move(NewState);
        
        if(!messagePassedToTheNewState.empty())
        {
            mNewState->mMessage = move(messagePassedToTheNewState);
        }
    }

    void StateManager::popCurrentState()
    {
        mRemoveState = true;
    }

    void StateManager::processStateChange()
    {
        if(mRemoveState && !mStateStack.empty())
        {
            mStateStack.pop();

            mRemoveState = false;
        }

        if(mAddState)
        {
            //check if there is envisaged to replace (add&replace) the current state, in case there is such a state. If so, remove it.
            if(mReplaceState && !mStateStack.empty())
            {
                mStateStack.pop();
            }

            //once the above prerpocessing is done, the mNewState can be added to the stack of states, then initialized and started
            mStateStack.push(move(mNewState));
            mStateStack.top()->initState();
            mAddState = false;
        }
    }

    std::unique_ptr<State>& StateManager::getCurrentState()
    {
        //the current state is the last state, stored at the top of the stack of states
        return mStateStack.top();
    }
}