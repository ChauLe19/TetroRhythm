#pragma once

#include <stack>
#include <memory>
#include "StateScreen.h"

class StateManager
{
private:
	std::stack<std::unique_ptr<StateScreen>> stateStack;
	std::unique_ptr<StateScreen> newState;

public:
	StateManager();
	~StateManager();

	void addState(std::unique_ptr<StateScreen> addState, bool isReplacing = true);
	void removeState();
	std::unique_ptr<StateScreen>& getCurrentState();

};

