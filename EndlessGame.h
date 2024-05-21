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
private:
	bool hsSaved = false;
public:
	EndlessGame(StateManager &stateManager, std::string folderPath);
	~EndlessGame();
	//sf::Clock clock;
	// Game Base functions
	//************************************************

	void tick(const float & dt, sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
	void render(sf::RenderWindow& window);

private:
	void gameOver();

};

#endif