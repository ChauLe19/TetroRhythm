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

	Button dropOnBeatGameButton = Button(sf::Color::White, 50, sf::Color::Transparent, "Drop On Beat", sf::Vector2f(200, 300), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button limitedGameButton = Button(sf::Color::White, 50, sf::Color::Transparent, "Limited Time", sf::Vector2f(200, 450), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button endlessGameButton = Button(sf::Color::White, 50, sf::Color::Transparent, "Endless", sf::Vector2f(200, 600), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button sprintGameButton = Button(sf::Color::White, 50, sf::Color::Transparent, "Sprint 40L", sf::Vector2f(200, 750), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button startButton = Button(sf::Color::White, 50, sf::Color::Transparent, "Start", sf::Vector2f(2048 / 2 - 100, 1000), sf::Vector2f(200, 100), sf::Color(0, 186, 211), sf::Keyboard::Enter);


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