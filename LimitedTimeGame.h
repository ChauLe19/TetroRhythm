/*****************************************************************//**
 * \file   EndlessGame.h
 * \brief  Game mode that will let player plays endlessly
 *
 * \author Chau Le
 * \date   August 2021
 *********************************************************************/
#ifndef LIMITED_TIME_GAME_H
#define LIMITED_TIME_GAME_H

#include "GameBase.h"

class LimitedTimeGame :
	public GameBase
{
public:
	LimitedTimeGame(Controls_Settings& settings);
	LimitedTimeGame(Controls_Settings& settings, string folderPath);
	~LimitedTimeGame();
	sf::Clock clock;
	// Game Base functions
	//************************************************

	void tick(State& state, RenderWindow& window);
	void tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window, Event event);
	void render(RenderWindow& window);


};

#endif