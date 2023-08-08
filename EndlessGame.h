/*****************************************************************//**
 * \file   EndlessGame.h
 * \brief  Game mode that will let player plays endlessly
 *
 * \author Chau Le
 * \date   August 2021
 *********************************************************************/
#pragma once
#ifndef ENDLESS_GAME_H
#define ENDLESS_GAME_H

#include "GameBase.h"

class EndlessGame :
	public GameBase
{
public:
	EndlessGame(StateManager &stateManager, string folderPath);
	~EndlessGame();
	//sf::Clock clock;
	// Game Base functions
	//************************************************

	void tick(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);
	void render(RenderWindow& window);


};

#endif