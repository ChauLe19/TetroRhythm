#include "GameSettings.h"
#include <fstream>
#include <iostream>
#include <sstream>

GameSettings* GameSettings::instance = NULL;

GameSettings::GameSettings()
{
}

GameSettings::~GameSettings()
{
}

GameSettings* GameSettings::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameSettings();
	}
	return instance;
}

GameSettings::Controls_Settings* GameSettings::getSettings()
{
	if (controlsSettings == nullptr)
	{
		controlsSettings = new Controls_Settings();
		initKeys();
		initConfig();
	}
	return controlsSettings;
}

GameSettings::Highscores* GameSettings::getHighscores()
{
	if (highscores == nullptr)
	{
		highscores = new Highscores();
		initHighscores();
	}
	return highscores;
}

void GameSettings::loadFiles()
{
	getSettings();
	getHighscores();
}

void GameSettings::saveKeys()
{
	ofstream outFile;
	outFile.open("Config/Keybinds.ini", ios::out);
	for (std::map<Controls_Key, sf::Keyboard::Key>::iterator it = controlsSettings->keybinds.begin(); it != controlsSettings->keybinds.end(); ++it)
	{
		outFile << controlsKeyStringMap.left.find(it->first)->second << ' ' << it->second << endl;
	}
	outFile.close();
}

void GameSettings::saveConfig()
{
	ofstream outFile;
	outFile.open("Config/Config.ini", ios::out);
	outFile << "SFX " << controlsSettings->sfx << endl;
	outFile << "MUSIC " << controlsSettings->music << endl;
	outFile.close();
}

void GameSettings::saveHighscores()
{
	std::cout << "save hs: " << highscores->limit << " " << highscores->endless << endl;
	ofstream outFile;
	outFile.open("Config/scores.sav", ios::out);
	outFile << highscores->limit << " " << highscores->endless << " " << highscores->sprintTime << endl;
	for (auto const& [name, score] : highscores->dropToBeatHS)
	{
		outFile << name << std::endl;	// song name
		outFile << score << std::endl;	// song highscore
	}
	outFile.close();
}

int GameSettings::getBeatMapThreshold(std::string songName)
{
	ifstream beatStream("BeatMaps/" + songName +"/"+ songName+ ".txt");
	int beatCount = 0;
	if (beatStream.is_open()) {
		char beat[10];
		while (beatStream.getline(beat, 10, '\r')) // read bpm
		{
			beatCount++;
		}
		// remove the first init line
		beatCount--;
	}

	cout << songName << " : " << 150 * beatCount << std::endl;
	return 150 * beatCount;
}

void GameSettings::initKeys()
{
	ifstream keybindsStream("Config/Keybinds.ini");
	controlsSettings->keybinds.clear();

	if (keybindsStream.is_open())
	{
		string key = "";
		int keyVal = 0;
		while (keybindsStream >> key >> keyVal)
		{
			controlsSettings->keybinds[controlsKeyStringMap.right.find(key)->second] = sf::Keyboard::Key(keyVal);
			std::cout << key << " " << keyVal << std::endl;
		}
	}
	keybindsStream.close();
}

void GameSettings::initConfig()
{
	ifstream configStream("Config/Config.ini");

	if (configStream.is_open())
	{
		string key = "";
		int keyVal = 0;
		while (configStream >> key >> keyVal)
		{
			if (key == "SFX")
			{
				controlsSettings->sfx = keyVal;
			}
			else if (key == "MUSIC")
			{
				controlsSettings->music = keyVal;
			}
		}
	}
	configStream.close();
}

void GameSettings::initHighscores()
{
	ifstream scoresStream("Config/scores.sav");
	if (scoresStream.is_open()) {
		std::string line("");
		int limitHS, endlessHS, sprintHS;
		// parse the first line
		if (std::getline(scoresStream, line));
		{
			std::istringstream iss(line);
			if (iss >> limitHS >> endlessHS >> sprintHS)
			{
				highscores->limit = limitHS;
				highscores->endless = endlessHS;
				highscores->sprintTime = sprintHS;
			}
		}

		std::string songName;
		int songHS;
		while (std::getline(scoresStream, line)) // read song name here
		{
			songName = std::string(line);
			highscores->dropToBeatThreshold.insert(std::pair<std::string, int> (songName, getBeatMapThreshold(songName)));
			if (std::getline(scoresStream, line))
			{
				std::istringstream iss(line);
				if (iss >> songHS) // read next line = song hs
				{
					highscores->dropToBeatHS.insert(std::pair<std::string, int>(songName, songHS));
				}
			}
		}
	}
}
