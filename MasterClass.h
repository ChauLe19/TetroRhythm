/*****************************************************************//**
 * \file   MasterClass.h
 * \brief  Control states and rendering
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#pragma once
#ifndef MASTER_CLASS_H
#define MASTER_CLASS_H

#include <SFML/Graphics.hpp>
#include "GameBase.h"
#include "Menu.h"
#include "Settings.h"
#include "Enums.h"
#include "GameOptions.h"
#include "MapEditorSelect.h"
#include "BeatMapEditor.h"
#include "ResultScreen.h"
#include <map>
#include "StateManager.h"

#define backgroundImagePath "images/background.png"
#define resolutionX 2048
#define resolutionY 1152

/**
 * Controls states and rendering.
 */
class MasterClass
{
public:
	static std::string BeatMapFolderPath;
private:
	sf::View m_view;
	sf::Clock clock;
	sf::Clock dtClock;
	float dt;
	sf::Text text;
	sf::Sprite backgroundSprite;

	sf::RenderWindow* window;
	StateManager stateManager;

	bool firstScroll = true;
public:
	MasterClass(sf::RenderWindow& window);
	~MasterClass();

	/**
	 * .Loop forever until close window
	 * Tick every frame.  Render state screen.
	 * 	If there is an event (example: keyboard input), do things accordingly
	 */
	void run();

	/**
	* Render graphics each frame on window screen
	*/
	void render();

	/**
	 * Life cycle function.
	 * Tick every frame
	 */
	void tick(const float & dt);


	/**
	 * Based on the key input and current state, do things accordingly. 
	 * Distribute keyEvent to the State_Screen's keyEvent
	 * 
	 * \param key: input from keyboard
	 */
	void keyEvent(const float & dt, sf::Event event);
	
	/**
	 * Based on the key input and current state, do things accordingly. 
	 * Distribute keyEvent to the State_Screen's mouseEvent
	 * 
	 * \param key: input from keyboard
	 */
	void mouseEvent(const float & dt, sf::Event event);

	/**
	 * Based on the key input and current state, do things accordingly. 
	 * Distribute keyEvent to the State_Screen's mouseScrolledEvent
	 * 
	 * \param key: input from keyboard
	 */
	void mouseScrolledEvent(const float & dt, sf::Event event);

	void updateDt();

	void loadResources();

};

#endif