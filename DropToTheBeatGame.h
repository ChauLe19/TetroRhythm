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
#include "Enums.h"
#include "Button.h"
#include "ResultScreen.h"
#include "Utils.h"
#include "GravityButton.h"

/**
 * Drop to the beat game mode.
 */
class DropToTheBeatGame :
	public GameBase
{
private:
	std::list<int> beatsTime;
	std::list<int> beatsTimeOriginal;

	int combo = 0;
	int maxCombo = 0;
	bool beatPressed = false;
	int bonus = 0;
	int beatAccuracyCount[3] = {0,0,0}; // miss || too late, almost, hit  
	int accuracyTimer = 0; 
	int health = 100; // 0 <= health <= 100
	int healthCounter = 0; // if reaches 60, health +=1 (every second, health +=1_
	int gravityCharge = 0; // if gravity charge is 100, the gravity can be activated
	int threshold = 0;
	GravityButton *gravityButton;

	void loadStaticAssets();
public:
	DropToTheBeatGame(StateManager &stateManager, std::string folderPath);
	~DropToTheBeatGame();



	std::string comboString="";
	HitType hitType = HitType::INVALID; // miss=0, almost=1, hit=2,

	// Game Base functions
	//*****************************************************

	void tick(const float & dt, sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
	void restart();
	void render(sf::RenderWindow& window);
	void renderBeatSignal(sf::RenderWindow& window);
private:
	void checkDropOnBeat(int beatTime);
	void gameOver();
	void activateGravity(int beatTime);
};
#endif
