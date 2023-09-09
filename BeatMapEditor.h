/*****************************************************************//**
 * \file   BeatMapEditor.h
 * \brief  Beat Map Editor screen that you can create/edit beat maps
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#pragma once
#ifndef BEAT_MAP_H
#define BEAT_MAP_H

#include "StateScreen.h"
#include "Enums.h"
#include "Utils.h"
#include "Button.h"
#include "MiniBpm.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include "StateManager.h"


using namespace std;
using namespace sf;
namespace fs = std::filesystem;

class BeatMapEditor : public StateScreen
{
private:
	Sound sound;
	SoundBuffer buffer;
	Text text;
	Button beatButton = Button(Color::Black, 50, Color(255, 255, 255, 200), "Beat", Vector2f(1024 + 1024 / 2 - 200, 1152 / 2 - 200), Vector2f(400, 400), Color(0, 186, 211), Keyboard::Key::Unknown);
	Button* speedButton025; // speed x0.25
	Button* speedButton050; // speed x0.5
	Button* speedButton100; // speed x1

	Button* dividerButton1; // divider 1
	Button* dividerButton12; // divider 1/2
	Button* dividerButton13; // divider 1/3
	Button* dividerButton14; // divider 1/4
	Board simulatorBoard = Board(100, 1152 / 2 - (boardSquareSize * boardHeight)/2);

	list<int> beatsTime;
	list<int>::iterator beatIt;

	string audioFilePath;
	string textFilePath;

	int musicDurationMS = 0;
	int bpm = 0;
	int mspb = 0; // ms per beat
	int cursorRelToMusicMS = 0;
	bool cursorSelected = false;

	int sliderLength = 2000;
	int sliderHeight = 100;
	int divider = 1;

	void loadStaticAssets();
public:
	BeatMapEditor(StateManager &stateManager, string folderPath);
	~BeatMapEditor();

	void save();
	void addCursorToBeatList();

	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);
};

#endif