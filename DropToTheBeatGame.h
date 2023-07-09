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
	int maxCombo = 0;
	bool beatPressed = false;
	int bonus = 0;
	int beatAccuracyCount[3] = {0,0,0}; // miss || too late, almost, hit  
	int accuracyTimer = 0; 
	int health = 100; // 0 <= health <= 100
	int healthCounter = 0; // if reaches 60, health +=1 (every second, health +=1_

public:
	DropToTheBeatGame(Controls_Settings& settings);
	DropToTheBeatGame(Controls_Settings& settings, string folderPath);
	~DropToTheBeatGame();


	string comboString="";
	int hitType = 0; // miss=0, almost=1, hit=2,

	// Game Base functions
	//*****************************************************

	void tick(State& state, RenderWindow& window);
	void tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window, Event event);
	void restart();
	void render(RenderWindow& window);
private:
	void checkDropOnBeat();
};
#endif
