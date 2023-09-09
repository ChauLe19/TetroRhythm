/*****************************************************************//**
 * \file   GameOptions.h
 * \brief  Game Options screen. Navigate to choose which game mode to play
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#pragma once
#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

#include "StateScreen.h"
#include "GameBase.h"
#include "DropToTheBeatGame.h"
#include "EndlessGame.h"
#include "LimitedTimeGame.h"
#include "Settings.h"
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
	Text text;
	bool choosingMap = false;
	int cursorMap = 0; // a table of game
	int cursorMode = 0;
	const int modeCount = 3;
	vector<fs::path> maps;
	int mapRenderOffset = 0;

	Button dropOnBeatGameButton = Button(Color::White, 50, Color::Transparent, "Drop On Beat", Vector2f(200, 300), Vector2f(500, 100), Color(0, 186, 211), Keyboard::A);
	Button limitedGameButton = Button(Color::White, 50, Color::Transparent, "Limited Time", Vector2f(200, 500), Vector2f(500, 100), Color(0, 186, 211), Keyboard::A);
	Button endlessGameButton = Button(Color::White, 50, Color::Transparent, "Endless", Vector2f(200, 700), Vector2f(500, 100), Color(0, 186, 211), Keyboard::A);
	Button startButton = Button(Color::White, 50, Color::Transparent, "Start", Vector2f(2048 / 2 - 100, 1000), Vector2f(200, 100), Color(0, 186, 211), Keyboard::Enter);


public:
	GameOptions(StateManager &stateManager);
	~GameOptions();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);

	/**
	 * Draw option out to window. If the cursor is on it, highlight it.
	 * 
	 * \param window
	 * \param gameMode String to be displayed
	 * \param x
	 * \param y
	 * \param isHighlight
	 */
	void drawGameModeOption(RenderTexture& window, string gameMode, int x, int y, bool isHighlight);
};

#endif