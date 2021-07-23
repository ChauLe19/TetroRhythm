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
#include "Settings.h"
#include "AutoDropGame.h"
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
	int cursorX = 0; // a table of game
	int cursorY = 0;
	GameBase*& gamePtr;
	Controls_Settings& settings;
public:
	GameOptions(GameBase*& gamePtr, Controls_Settings& settings);
	~GameOptions();

	// StateScreen functions
	//****************************************************
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
};

#endif