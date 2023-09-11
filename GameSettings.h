#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;

// singleton class for loading game settings
class GameSettings
{
public:
	struct Controls_Settings {
		std::map<std::string, sf::Keyboard::Key> keybinds;
		int sfx = 0;
		int music = 0;
	};

	struct Highscores {
		std::map<std::string, int> dropToBeatHS;
		std::map<std::string, int> dropToBeatThreshold;
		int endless = 0;
		int limit = 0;
	};

	static Controls_Settings* getSettings();
	static Highscores* getHighscores();
	static void loadFiles();

	static void saveKeys();
	static void saveConfig();
	static void saveHighscores();
	static int getBeatMapThreshold(std::string songName);
private:
	static Controls_Settings* controlsSettings;
	static Highscores* highscores;
	GameSettings();
	~GameSettings();

	static void initKeys();
	static void initConfig();
	static void initHighscores();
};

