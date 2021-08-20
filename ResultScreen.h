/*****************************************************************//**
 * \file   ResultScreen.h
 * \brief  Results Screen after finishing a song. Calculate letter ranking and adjusted score.
 *			Display accuracy, raw score, and adjusted score.
 *
 * \author Chau Le
 * \date   August 2021
 *********************************************************************/

#ifndef RESULT_SCREEN_H
#define RESULT_SCREEN_H
#include "StateScreen.h"

using namespace std;
class GameBase;
class DropToTheBeatGame;
class ResultScreen :
	public StateScreen
{
private:
	float accuracy = 0; // percentage = (almostCount + 2*hitCount)/(2*(almostCount + hitCount + missCount)
	int rawScore = 0;
	int adjustedScore = 0; // adjustedScore = accuracyPercentage * rawScore
	int combo = 0;
	int accuracyBeatCount[3];
	string letterRanked;
	//GameBase* game;

	Text text;
	Font font;
public:
	ResultScreen(int accuracyBeatCount[3], int rawScore, int combo);
	~ResultScreen();

	// StateScreen functions
	//****************************************************
	void tick(State& state, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void keyEvent(State& state, Keyboard::Key key, GameBase*& game);
	void mouseEvent(State& state, RenderWindow& window);

};
#endif

