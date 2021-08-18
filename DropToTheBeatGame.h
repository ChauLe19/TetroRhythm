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
	int health = 100; // 0 <= health <= 100
	int healthCounter = 0; // if reaches 60, health +=1 (every second, health +=1_
	int bonus = 0;
public:
	DropToTheBeatGame(Controls_Settings& settings);
	DropToTheBeatGame(Controls_Settings& settings, string folderPath);
	~DropToTheBeatGame();


	string comboString="";
	int hitType = 0; // miss=0, almost=1, hit=2,

	// Game Base functions
	//*****************************************************

	void tick(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void render(RenderWindow& window);
};
#endif
