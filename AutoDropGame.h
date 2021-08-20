/*****************************************************************//**
 * \file   AutoDropGame.h
 * \brief  Game mode that will drop when the beat is played.
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#ifndef AUTO_DROP_GAME_H
#define  AUTO_DROP_GAME_H

#include "GameBase.h"

/**
 * Auto drop game mode.
 */
class AutoDropGame :
	public GameBase
{
public:
	AutoDropGame(Controls_Settings& settings);
	AutoDropGame(Controls_Settings& settings, string folderPath);
	~AutoDropGame();
	
	// Game Base functions
	//************************************************

	void tick(State& state, RenderWindow& window);
	void tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window);
	void render(RenderWindow& window);


	/**
	 * If the beat is played, drop the current tetromino.
	 * 
	 */
	void dropOnBeat();
};

#endif