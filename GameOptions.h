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
#include "SprintGame.h"
#include "Settings.h"
#include "ResultScreen.h"
#include "Enums.h"

#include <SFML/Graphics.hpp>

/**
 * Controls Game Options screen.
 */
class GameOptions : public StateScreen
{
private:
	sf::Music previewMusic;
	sf::Sprite songBackground;

	sf::Text text;
	bool choosingMap = false;
	int cursorMap = 0; // a table of game
	int cursorMode = 0;
	const int modeCount = 4;
	std::vector<fs::path> maps;
	int mapRenderOffset = 0;
	int prevMapRenderOffset = 0;

	Button dropOnBeatGameButton = Button(sf::Text("Drop On Beat", getAssetManager()->getFont("game font"), 50U));
	Button limitedGameButton = Button(sf::Text("Limited Time", getAssetManager()->getFont("game font"), 50U));
	Button endlessGameButton = Button(sf::Text("Endless", getAssetManager()->getFont("game font"), 50U));
	Button sprintGameButton = Button(sf::Text("Sprint 40L", getAssetManager()->getFont("game font"), 50U));
	Button startButton = Button(sf::Text("Start", getAssetManager()->getFont("game font"), 50U));

public:
	GameOptions(StateManager &stateManager);
	~GameOptions();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
	void mouseScrollEvent(const float & dt, sf::RenderWindow& window, sf::Event event);

	/**
	 * Draw option out to window. If the cursor is on it, highlight it.
	 * 
	 * \param window
	 * \param gameMode String to be displayed
	 * \param x
	 * \param y
	 * \param isHighlight
	 */
	void drawGameModeOption(sf::RenderTexture& window, std::string gameMode, int x, int y, bool isHighlight);
private:
	void selectMap(int mapIndex);
	void startGame();
};

#endif