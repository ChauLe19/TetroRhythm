#pragma once
#include "GameBase.h"
class DropToTheBeatGame :
	public GameBase
{
public:
	DropToTheBeatGame(Controls_Settings& settings);
	~DropToTheBeatGame();
	void tick(RenderWindow& window);
	void dropOnBeat();
	void keyEvent(State& state, Keyboard::Key key);
};

