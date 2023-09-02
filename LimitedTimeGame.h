/*****************************************************************//**
 * \file   EndlessGame.h
 * \brief  Game mode that will let player plays endlessly
 *
 * \author Chau Le
 * \date   August 2021
 *********************************************************************/
#pragma once
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

	void tick(const float & dt, RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);
	void render(RenderWindow& window);

private:
	void gameOver();

};

#endif