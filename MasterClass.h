/*****************************************************************//**
 * \file   MasterClass.h
 * \brief  Control states and rendering
 * 
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

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
#include <map>
/**
 * Controls states and rendering.
 */
class MasterClass
{
public:
	static string BeatMapFolderPath;
private:
	typedef Settings::Controls_Settings Controls_Settings;
	Controls_Settings controlsSettings;
	Clock clock;
	Font font;
	Text text;

	State state = State::MENU;

	// All state screens
	//**************************************************

	Menu* menu;
	GameBase* game;
	Settings* settings;
	RenderWindow* window;
	GameOptions* gameOptions;
	MapEditorSelect* mapEditorSelect;
	BeatMapEditor* beatMapEditor;


public:
	MasterClass(RenderWindow& window);
	~MasterClass();

	void initKeys();
	void initConfig();

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
	void tick();


	/**
	 * Based on the key input and current state, do things accordingly. 
	 * Distribute keyEvent to the State_Screen's keyEvent
	 * 
	 * \param key: input from keyboard
	 */
	void keyEvent(Keyboard::Key key);
	
	/**
	 * Based on the key input and current state, do things accordingly. 
	 * Distribute keyEvent to the State_Screen's keyEvent
	 * 
	 * \param key: input from keyboard
	 */
	void mouseEvent();

	void openBeatMapEditor(string folderPath);

};

#endif