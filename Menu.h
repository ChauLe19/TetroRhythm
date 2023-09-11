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

using namespace sf;
using namespace std;

/**
 * Controls menu screen.
 */
class Menu : public StateScreen
{
private:
	Text text;
	Sprite buttonImage;
	Button beginButton = Button(Color::White, 50, Color::Transparent, "PLAY", Vector2f(1024 - 250, 450), Vector2f(500, 100), Color(0, 186, 211), Keyboard::A);
	Button beatmapButton = Button(Color::White, 50, Color::Transparent, "EDIT BEAT MAPS", Vector2f(1024 - 250, 570), Vector2f(500, 100), Color(0, 186, 211), Keyboard::A);
	Button tutorialButton = Button(Color::White, 50, Color::Transparent, "TUTORIAL", Vector2f(1024 - 250, 690), Vector2f(500, 100), Color(0, 186, 211), Keyboard::A);
	Button settingsButton = Button(Color::White,40, Color::Transparent, "Settings", Vector2f(1024 - 250, 810), Vector2f(240, 100), Color(0, 186, 211), Keyboard::A);
	Button exitButton = Button(Color::White,40, Color::Transparent, "Exit", Vector2f(1024 + 10, 810), Vector2f(240, 100), Color(0, 186, 211), Keyboard::A);

public:
	Menu(StateManager &stateManager);
	~Menu();

	// StateScreen functions
	//**************************************************

	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);
};
#endif
