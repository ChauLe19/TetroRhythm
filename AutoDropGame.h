#ifndef AUTO_DROP_GAME_H
#define  AUTO_DROP_GAME_H

#include "GameBase.h"
class AutoDropGame :
	public GameBase
{
public:
	AutoDropGame(Controls_Settings& settings);
	~AutoDropGame();
	void tick(RenderWindow& window);
	void dropOnBeat();
	void keyEvent(State& state, Keyboard::Key key);
};

#endif