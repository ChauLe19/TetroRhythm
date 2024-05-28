#include "StateManager.h"

StateManager::StateManager(Context context) : context(context)
{
}

StateManager::~StateManager()
{
}

void StateManager::addState (std::unique_ptr<StateScreen> newState, bool isReplacing)
{
	if (!stateStack.empty())
	{
		if (isReplacing)
		{
			stateStack.pop();
		}
		else
		{
			this->stateStack.top()->pause();
		}
	}

	this->stateStack.push(std::move(newState));
	this->stateStack.top()->init();
}

void StateManager::removeState()
{
    if (!stateStack.empty())
    {
        stateStack.pop();

        if (!stateStack.empty())
        {
            // start state
            this->stateStack.top()->resume();
        }
    }
}

StateManager::Context& StateManager::getContext()
{
	return context;
}

std::unique_ptr<StateScreen>& StateManager::getCurrentState()
{
    return this->stateStack.top();
}

StateManager::Context::Context(sf::RenderWindow* window, AssetManager* assetManager) : window(window), assetManager(assetManager)
{
}
