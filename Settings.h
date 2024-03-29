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

using namespace sf;
using namespace std;

const string controlsList[8] = { "HOLD","HARD_DROP","HARD_DROP_ALT" };
class Settings : public StateScreen
{
public:
private:
	Text text;
	GameSettings::Controls_Settings* settings = GameSettings::getInstance()->getSettings();
	int cursor = 0;
	bool isChanging = false;

	/**
	 * Map the key to its string representation.
	 *
	 * \param k Keyboard key
	 * \return String representation of key
	 */
	string fromKtoS(const sf::Keyboard::Key& k);

	/**
	* Map the action to its string representation.
	*
	* \param k Controls key
	* \return String representation of the action
	*/
	string fromControlsToString(Controls_Key key);
public:

	Settings(StateManager &stateManager);
	~Settings();

	// GameBase functions
	//********************************************

	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);

	/**
	 * Draw option
	 */
	void drawKeyConfig(string name, string key, int x, int y, RenderWindow& window, bool isHighlight, bool changing);

	/**
	 * Switch out the key at current cursor to the key in argument.
	 */
	bool changeKey(Keyboard::Key key);

	/**
	 * Set cursor. At the same time clamp the cursor from 0 to 9.
	 */
	void setCursor(int cursor);
};
#endif

