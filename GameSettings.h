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

	static Controls_Settings getSettings();
	static void loadFiles();
private:
	static Controls_Settings* controlsSettings;
	GameSettings();
	~GameSettings();

	static void initKeys();
	static void initConfig();
};

