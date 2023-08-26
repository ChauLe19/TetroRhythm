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

	void tick(const float & dt, RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);
	void render(RenderWindow& window);


};

#endif