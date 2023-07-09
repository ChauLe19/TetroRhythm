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
	EndlessGame(Controls_Settings& settings, string folderPath);
	~EndlessGame();
	//sf::Clock clock;
	// Game Base functions
	//************************************************

	void tick(State& state, RenderWindow& window);
	void tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window, Event event);
	void render(RenderWindow& window);


};

#endif