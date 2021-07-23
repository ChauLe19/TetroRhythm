#pragma once
#include "GameBase.h"
class DropToTheBeatGame :
	public GameBase
{
public:
	DropToTheBeatGame(array<Keyboard::Key, 8>& keyMap);
	~DropToTheBeatGame();
	void tick(RenderWindow& window);
	void dropOnBeat();
	void keyEvent(State& state, Keyboard::Key key);
};

