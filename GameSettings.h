#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Enums.h"

// singleton class for loading game settings
class GameSettings
{
public:
	struct Controls_Settings {
		std::map<Controls_Key, sf::Keyboard::Key> keybinds;
		int sfx = 0;
		int music = 0;
	};

	struct Highscores {
		std::map<std::string, int> dropToBeatHS;
		std::map<std::string, int> dropToBeatThreshold;
		int endless = 0;
		int limit = 0;
		int sprintTime = INT_MAX; // time in miliseconds, the lower the better
	};

	static GameSettings* getInstance();

	Controls_Settings* getSettings();
	Highscores* getHighscores();
	void loadFiles();

	void saveKeys();
	void saveConfig();
	void saveHighscores();
	int getBeatMapThreshold(std::string songName);
private:
	static GameSettings* instance;
	Controls_Settings* controlsSettings;
	Highscores* highscores;
	GameSettings();
	~GameSettings();

	void initKeys();
	void initConfig();
	void initHighscores();
};

