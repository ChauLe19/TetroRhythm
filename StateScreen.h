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

class StateManager;
class StateScreen
{
public:
	struct Context
	{
		Context(sf::RenderWindow* window, AssetManager* assetManager);
		sf::RenderWindow* window;
		AssetManager* assetManager = AssetManager::getInstance();
	};
private:
protected:
	Context m_context;
	sf::Texture backgroundTexture;
	sf::Sprite* background = nullptr;
	StateManager &stateManager;

	virtual void loadStaticAssets() {};
public:
	StateScreen(StateManager& stateManager, Context context);
	~StateScreen();

	AssetManager* getAssetManager() const;
	/**
	 * Life cycle function. Run each frame.
	 *
	 * \param window Rendering window
	 */
	virtual void tick(const float & dt, sf::RenderWindow& window) = 0;

	/**
	 * Function for drawing the screen.
	 *
	 * \param window Rendering window
	 */
	virtual void render(sf::RenderWindow& window) {
		window.clear();
		if (background)
		{
			window.draw(*background);
		}
	};

	/**
	 * Function run when a keyboard key event is detected.
	 *
	 * \param state Which the app is in
	 *
	 * \param key Was pressed
	 */
	virtual void keyEvent(const float & dt, sf::Event event) = 0;

	/**
	 * Function run when a mouse event is detected.
	 *
	 */
	virtual void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event) = 0;
	
	/**
	 * Function run when a mouse scroll event is detected.
	 *
	 */
	virtual void mouseScrollEvent(const float & dt, sf::RenderWindow& window, sf::Event event) {};

	virtual void init() {};
	virtual void pause() {};
	virtual  void resume() {};
};

#endif