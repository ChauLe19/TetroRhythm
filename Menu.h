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
	Button beginButton;
	Button beatmapButton;
	Button tutorialButton;
	Button settingsButton;
	Button exitButton;

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
