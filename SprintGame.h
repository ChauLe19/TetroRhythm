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
	SprintGame(StateManager &stateManager, Context context, std::string folderPath);
	~SprintGame();
	// Game Base functions
	//************************************************

	void tick(const float & dt, sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
	void render(sf::RenderWindow& window);

private:
	void gameOver();
	void restart();

};

#endif
