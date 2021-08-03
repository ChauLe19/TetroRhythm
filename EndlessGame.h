/*****************************************************************//**
 * \file   EndlessGame.h
 * \brief  Game mode that will let player plays endlessly
 *
 * \author Chau Le
 * \date   August 2021
 *********************************************************************/
#ifndef ENDLESS_GAME_H
#define ENDLESS_GAME_H

#include "GameBase.h"

class EndlessGame :
	public GameBase
{
public:
	EndlessGame(Controls_Settings& settings);
	~EndlessGame();

	// Game Base functions
	//************************************************

	void tick(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void render(RenderWindow& window);


};

#endif