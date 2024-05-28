#pragma once

#include <stack>
#include <memory>
#include "StateScreen.h"

class StateManager
{
public:
	struct Context
	{
		Context(sf::RenderWindow* window, AssetManager* assetManager);
		sf::RenderWindow* window;
		AssetManager* assetManager = AssetManager::getInstance();
	};
private:
	std::stack<std::unique_ptr<StateScreen>> stateStack;
	std::unique_ptr<StateScreen> newState;
	Context context;

public:
	StateManager(Context context);
	~StateManager();

	void addState(std::unique_ptr<StateScreen> addState, bool isReplacing = true);
	void removeState();
	Context& getContext();
	std::unique_ptr<StateScreen>& getCurrentState();

};

