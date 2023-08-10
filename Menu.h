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

public:
	Menu(StateManager &stateManager);
	~Menu();

	// StateScreen functions
	//**************************************************

	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);
};
#endif
