/*****************************************************************//**
 * \file   DropToTheBeatGame.h
 * \brief  Game mode that requires player to 
 * hard drop when there is a beat to keep the combo.
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#ifndef DROP_TO_BEAT_H
#define DROP_TO_BEAT_H

#include "GameBase.h"

/**
 * Drop to the beat game mode.
 */
class DropToTheBeatGame :
	public GameBase
{
private:
	int combo = 0;
	bool beatPressed = false;
public:
	DropToTheBeatGame(Controls_Settings& settings);
	DropToTheBeatGame(Controls_Settings& settings, string folderPath);
	~DropToTheBeatGame();

	// Game Base functions
	//*****************************************************

	void tick(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void render(RenderWindow& window);
};
#endif
