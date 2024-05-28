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
private:
	sf::Clock clock;
public:
	LimitedTimeGame(StateManager &stateManager, Context context, std::string folderPath);
	~LimitedTimeGame();

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