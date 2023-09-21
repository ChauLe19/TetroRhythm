/*****************************************************************//**
 * \file   SprintGame.h
 * \brief  Game mode that users have to race to finish clearing 40L
 *
 * \author Chau Le
 * \date   Sept 2023
 *********************************************************************/
#pragma once
#ifndef SPRINT_GAME_H
#define SPRINT_GAME_H

#include "GameBase.h"
#include "Button.h"

class SprintGame :
	public GameBase
{
private:
	sf::Clock timer;
	bool hsSaved = false;
	sf::Int32 currSprintTime;
public:
	SprintGame(StateManager &stateManager, string folderPath);
	~SprintGame();
	// Game Base functions
	//************************************************

	void tick(const float & dt, RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);
	void render(RenderWindow& window);

private:
	void gameOver();
	void restart();

};

#endif
