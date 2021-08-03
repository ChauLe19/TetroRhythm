/*****************************************************************//**
 * \file   BeatMapEditor.h
 * \brief  Beat Map Editor screen that you can create/edit beat maps
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#ifndef BEAT_MAP_H
#define BEAT_MAP_H

#include "StateScreen.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
using namespace sf;

class BeatMapEditor : public StateScreen
{
private:
	Sound sound;
	SoundBuffer buffer;
	ifstream inFile;
	ofstream outFile;

	list<int> beatsTime;
	list<int>::iterator beatIt;

	string audioFilePath;
	string textFilePath;

	int musicDurationMS = 0;
	int cursorRelToMusicMS = 0;
	bool firstPressed = true;
	bool cursorSelected = false;

	int sliderLength = 2000;
	int sliderHeight = 100;
public:
	BeatMapEditor(string audioFilePath);
	BeatMapEditor(string audioFilePath, string textFilePath);
	~BeatMapEditor();

	void save();

	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
	void mouseEvent(RenderWindow& window);
};

#endif