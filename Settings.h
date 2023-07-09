/*****************************************************************//**
 * \file   Settings.h
 * \brief  Settings screen. Config key controls and delay.
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "StateScreen.h"
#include "Enums.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>

using namespace sf;
using namespace std;

const string controlsList[8] = { "MOVE_LEFT","MOVE_RIGHT","ROTATE_CCW","ROTATE_CW","ROTATE_180","HOLD","HARD_DROP","SOFT_DROP" };
class Settings : public StateScreen
{
public:
	struct Controls_Settings {
		map<string, Keyboard::Key> keybinds;
		int delayAutoShift;
		int autoRepeatRate;
	};
private:
	Text text;
	Font font;
	Controls_Settings& settings;
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

	Settings(Controls_Settings& settings);
	~Settings();

	// GameBase functions
	//********************************************

	void tick(State& state, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(State& state, RenderWindow& window, Event event);

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

