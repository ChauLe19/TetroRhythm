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
	Button* speedButton025;
	Button* speedButton050;
	Button* speedButton100;

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
public:
	BeatMapEditor(StateManager &stateManager, string folderPath);
	~BeatMapEditor();

	void save();
	void addCursorToBeatList();

	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);
};

#endif