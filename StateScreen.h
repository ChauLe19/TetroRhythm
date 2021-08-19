/*****************************************************************//**
 * \file   StateScreen.h
 * \brief  Abstract class for screen at each state
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#ifndef STATE_SCREEN_H
#define STATE_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Enums.h"

using namespace sf;

class StateScreen
{
public:
	/**
	 * Life cycle function. Run each frame.
	 *
	 * \param window Rendering window
	 */
	virtual void tick(State& state, RenderWindow& window) = 0;

	/**
	 * Function for drawing the screen.
	 *
	 * \param window Rendering window
	 */
	virtual void render(RenderWindow& window) = 0;

	/**
	 * Function run when a keyboard key event is detected.
	 *
	 * \param state Which the app is in
	 *
	 * \param key Was pressed
	 */
	virtual void keyEvent(State& state, Keyboard::Key key) = 0;

	/**
	 * Function run when a mouse event is detected.
	 *
	 */
	virtual void mouseEvent(State& state, RenderWindow& window) = 0;
};

#endif