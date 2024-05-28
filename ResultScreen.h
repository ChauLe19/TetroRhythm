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

class ResultScreen :
	public StateScreen
{
private:
	std::string songName;
	float accuracy = 0; // percentage = (almostCount + 2*hitCount)/(2*(almostCount + hitCount + missCount)
	int rawScore = 0;
	int adjustedScore = 0; // adjustedScore = accuracyPercentage * rawScore
	int combo = 0;
	int accuracyBeatCount[3];
	std::string letterRanked;

	sf::Text text;
public:
	ResultScreen(StateManager& stateManager, Context context, std::string folderPath, int accuracyBeatCount[3], int rawScore, int combo);
	~ResultScreen();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);

};
#endif

