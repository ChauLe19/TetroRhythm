/*****************************************************************//**
 * \file   Menu.h
 * \brief  Menu Screen. Go to game options or settings screen
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#ifndef MENU_H
#define MENU_H

#include "StateScreen.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "GameOptions.h"
#include "Settings.h"
#include "MapEditorSelect.h"

/**
 * Controls menu screen.
 */
class Menu : public StateScreen
{
private:
	sf::Text text;
	sf::Sprite buttonImage;
	Button beginButton = Button(sf::Color::White, 50, sf::Color::Transparent, "PLAY", sf::Vector2f(1024 - 250, 450), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button beatmapButton = Button(sf::Color::White, 50, sf::Color::Transparent, "EDIT BEAT MAPS", sf::Vector2f(1024 - 250, 570), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button tutorialButton = Button(sf::Color::White, 50, sf::Color::Transparent, "TUTORIAL", sf::Vector2f(1024 - 250, 690), sf::Vector2f(500, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button settingsButton = Button(sf::Color::White,40, sf::Color::Transparent, "Settings", sf::Vector2f(1024 - 250, 810), sf::Vector2f(240, 100), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button exitButton = Button(sf::Color::White,40, sf::Color::Transparent, "Exit", sf::Vector2f(1024 + 10, 810), sf::Vector2f(240, 100), sf::Color(0, 186, 211), sf::Keyboard::A);

public:
	Menu(StateManager &stateManager);
	~Menu();

	// StateScreen functions
	//**************************************************

	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
};
#endif
