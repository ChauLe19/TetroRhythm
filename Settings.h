/*****************************************************************//**
 * \file   Settings.h
 * \brief  Settings screen. Config key controls and delay.
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include "StateScreen.h"
#include "Enums.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include "GameSettings.h"
#include "StateManager.h"

const std::string controlsList[8] = { "HOLD","HARD_DROP","HARD_DROP_ALT" };
class Settings : public StateScreen
{
public:
private:
	sf::Text text;
	GameSettings::Controls_Settings* settings = GameSettings::getInstance()->getSettings();
	int cursor = 0;
	bool isChanging = false;

	/**
	 * Map the key to its string representation.
	 *
	 * \param k Keyboard key
	 * \return String representation of key
	 */
	std::string fromKtoS(const sf::Keyboard::Key& k);

	/**
	* Map the action to its string representation.
	*
	* \param k Controls key
	* \return String representation of the action
	*/
	std::string fromControlsToString(Controls_Key key);
public:

	Settings(StateManager &stateManager, Context context);
	~Settings();

	// GameBase functions
	//********************************************

	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);

	/**
	 * Draw option
	 */
	void drawKeyConfig(std::string name, std::string key, int x, int y, sf::RenderWindow& window, bool isHighlight, bool changing);

	/**
	 * Switch out the key at current cursor to the key in argument.
	 */
	bool changeKey(sf::Keyboard::Key key);

	/**
	 * Set cursor. At the same time clamp the cursor from 0 to 9.
	 */
	void setCursor(int cursor);
};
#endif

