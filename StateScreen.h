/*****************************************************************//**
 * \file   StateScreen.h
 * \brief  Abstract class for screen at each state
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#pragma once
#ifndef STATE_SCREEN_H
#define STATE_SCREEN_H

#include <SFML/Graphics.hpp>
#include "AssetManager.h"


using namespace sf;

class StateManager;
class StateScreen
{
private:
protected:
	StateManager &stateManager;
	AssetManager* assetManager = AssetManager::getInstance();

	virtual void loadStaticAssets() {};
public:
	StateScreen(StateManager& stateManager);
	~StateScreen();
	/**
	 * Life cycle function. Run each frame.
	 *
	 * \param window Rendering window
	 */
	virtual void tick(const float & dt, RenderWindow& window) = 0;

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
	virtual void keyEvent(const float & dt, Event event) = 0;

	/**
	 * Function run when a mouse event is detected.
	 *
	 */
	virtual void mouseEvent(const float & dt, RenderWindow& window, Event event) = 0;
	
	/**
	 * Function run when a mouse scroll event is detected.
	 *
	 */
	virtual void mouseScrollEvent(const float & dt, Event event) {};


	virtual void init() {};
	virtual void pause() {};
	virtual  void resume() {};
};

#endif