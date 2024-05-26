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
#include "ButtonGroup.h"

namespace fs = std::filesystem;

class BeatMapEditor : public StateScreen
{
private:
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Text text;
	Button beatButton = Button(sf::Text("Beat", assetManager->getFont("game font"), 50));
	ButtonGroup speedButtonGroup; // speed x0.25
	Button* speedButton025; // speed x0.25
	Button* speedButton050; // speed x0.5
	Button* speedButton100; // speed x1

	ButtonGroup dividerButtonGroup; // speed x0.25
	Button* dividerButton1; // divider 1
	Button* dividerButton12; // divider 1/2
	Button* dividerButton13; // divider 1/3
	Button* dividerButton14; // divider 1/4
	Board simulatorBoard = Board(100, 1152 / 2 - (boardSquareSize * boardHeight)/2);

	std::list<int> beatsTime;
	std::list<int>::iterator beatIt;

	std::string audioFilePath;
	std::string textFilePath;

	int musicDurationMS = 0;
	int bpm = 0;
	int mspb = 0; // ms per beat
	int cursorRelToMusicMS = 0;
	bool cursorSelected = false;

	int sliderLength = 2000;
	int sliderHeight = 100;
	int divider = 1;

	void loadStaticAssets();
	void setDivider(int divider);
public:
	BeatMapEditor(StateManager &stateManager, std::string folderPath);
	~BeatMapEditor();

	void save();
	void addCursorToBeatList();

	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
};

#endif