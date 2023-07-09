/*****************************************************************//**
 * \file   GameOptions.h
 * \brief  Game Options screen. Navigate to choose which game mode to play
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

#include "StateScreen.h"
#include "GameBase.h"
#include "DropToTheBeatGame.h"
#include "EndlessGame.h"
#include "LimitedTimeGame.h"
#include "Settings.h"
#include "AutoDropGame.h"
#include "ResultScreen.h"
#include "Enums.h"

#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * Controls Game Options screen.
 */
class GameOptions : public StateScreen
{
private:
	typedef Settings::Controls_Settings Controls_Settings;
	Text text;
	Font font;
	bool choosingMap = false;
	int cursorMap = 0; // a table of game
	int cursorMode = 0;
	GameBase*& gamePtr;
	Controls_Settings& settings;
	const int modeCount = 4;
	vector<fs::path> maps;


public:
	GameOptions(GameBase*& gamePtr, Controls_Settings& settings);
	~GameOptions();

	// StateScreen functions
	//****************************************************
	void tick(State& state, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window, Event event);

	/**
	 * Draw option out to window. If the cursor is on it, highlight it.
	 * 
	 * \param window
	 * \param gameMode String to be displayed
	 * \param x
	 * \param y
	 * \param isHighlight
	 */
	void drawGameModeOption(RenderWindow& window, string gameMode, int x, int y, bool isHighlight);
};

#endif