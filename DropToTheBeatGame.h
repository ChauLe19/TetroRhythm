/*****************************************************************//**
 * \file   DropToTheBeatGame.h
 * \brief  Game mode that requires player to 
 * hard drop when there is a beat to keep the combo.
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#pragma once
#ifndef DROP_TO_BEAT_H
#define DROP_TO_BEAT_H

#include "GameBase.h"
#include "Button.h"

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
	Button *clearBoardButton;

public:
	DropToTheBeatGame(StateManager &stateManager, string folderPath);
	~DropToTheBeatGame();


	string comboString="";
	int hitType = 0; // miss=0, almost=1, hit=2,

	// Game Base functions
	//*****************************************************

	void tick(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);
	void restart();
	void render(RenderWindow& window);
private:
	void checkDropOnBeat();
};
#endif
