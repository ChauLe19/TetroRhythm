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
	LimitedTimeGame(StateManager &stateManager, string folderPath);
	~LimitedTimeGame();
	sf::Clock clock;
	// Game Base functions
	//************************************************

	void tick(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);
	void render(RenderWindow& window);


};

#endif