#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

#include "StateScreen.h"
#include "GameBase.h"
#include "DropToTheBeatGame.h"
#include "AutoDropGame.h"
#include <SFML/Graphics.hpp>
#include "Enums.h"
using namespace sf;

class GameOptions : public StateScreen
{
private:
	Text text;
	Font font;
	int cursorX = 0; // a table of game
	int cursorY = 0;
	GameBase*& gamePtr;
	array<Keyboard::Key, 8>& keyMap;
public:
	GameOptions(GameBase*& gamePtr, array<Keyboard::Key, 8>& keyMap);
	~GameOptions();
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
};

#endif