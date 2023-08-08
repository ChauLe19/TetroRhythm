#include "GameSettings.h"
#include <fstream>
GameSettings::Controls_Settings* GameSettings::controlsSettings = NULL;

GameSettings::GameSettings()
{
}

GameSettings::~GameSettings()
{
}

GameSettings::Controls_Settings GameSettings::getSettings()
{
	if (controlsSettings == nullptr)
	{
		controlsSettings = new Controls_Settings();
		loadFiles();
	}
	return *controlsSettings;
}

void GameSettings::loadFiles()
{
	initKeys();
	initConfig();
}

void GameSettings::initKeys()
{
	ifstream keybindsStream("Config/Keybinds.txt");
	controlsSettings->keybinds.clear();

	if (keybindsStream.is_open())
	{
		string key = "";
		int keyVal = 0;
		while (keybindsStream >> key >> keyVal)
		{
			controlsSettings->keybinds[key] = sf::Keyboard::Key(keyVal);
		}
	}
	keybindsStream.close();
}

void GameSettings::initConfig()
{
	ifstream configStream("Config/Config.txt");

	if (configStream.is_open())
	{
		string key = "";
		int keyVal = 0;
		while (configStream >> key >> keyVal)
		{
			if (key == "DAS")
			{
				controlsSettings->delayAutoShift = keyVal;
			}
			else if (key == "ARR")
			{
				controlsSettings->autoRepeatRate = keyVal;
			}
		}
	}
	configStream.close();
}
