/*****************************************************************//**
 * \file   ResultScreen.h
 * \brief  Results Screen after finishing a song. Calculate letter ranking and adjusted score.
 *			Display accuracy, raw score, and adjusted score.
 *
 * \author Chau Le
 * \date   August 2021
 *********************************************************************/

#pragma once
#ifndef RESULT_SCREEN_H
#define RESULT_SCREEN_H
#include "StateScreen.h"

using namespace std;
class ResultScreen :
	public StateScreen
{
private:
	string songName;
	float accuracy = 0; // percentage = (almostCount + 2*hitCount)/(2*(almostCount + hitCount + missCount)
	int rawScore = 0;
	int adjustedScore = 0; // adjustedScore = accuracyPercentage * rawScore
	int combo = 0;
	int accuracyBeatCount[3];
	string letterRanked;

	Text text;
public:
	ResultScreen(StateManager& stateManager, string folderPath, int accuracyBeatCount[3], int rawScore, int combo);
	~ResultScreen();

	// StateScreen functions
	//****************************************************
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);

};
#endif

