#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

#include "StateScreen.h"
#include "GameBase.h"
#include "DropToTheBeatGame.h"
#include "Settings.h"
#include "AutoDropGame.h"
#include <SFML/Graphics.hpp>
#include "Enums.h"
using namespace sf;

class GameOptions : public StateScreen
{
private:
	typedef Settings::Controls_Settings Controls_Settings;
	Text text;
	Font font;
	int cursorX = 0; // a table of game
	int cursorY = 0;
	GameBase*& gamePtr;
	Controls_Settings& settings;
public:
	GameOptions(GameBase*& gamePtr, Controls_Settings& settings);
	~GameOptions();
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
};

#endif