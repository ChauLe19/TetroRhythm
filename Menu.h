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

using namespace sf;
using namespace std;

/**
 * Controls menu screen.
 */
class Menu : public StateScreen
{
private:
	Text text;
	Font font;
	Texture buttonTexture;
	Sprite buttonImage;
	bool firstPressed = false;
public:
	Menu();
	~Menu();

	// StateScreen functions
	//**************************************************

	void tick(State& state, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window);
};
#endif
