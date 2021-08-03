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

#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * Controls menu screen.
 */
class Menu : public StateScreen
{
private:
	Text text;
	Font font;
public:
	Menu();
	~Menu();

	// StateScreen functions
	//**************************************************

	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(RenderWindow& window);
};
#endif
