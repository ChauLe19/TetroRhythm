#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

#include <SFML/Graphics.hpp>
using namespace sf;

class GameOptions
{
private:
	Text text;
	Font font;
	int cursorX; // a table of game
	int cursorY;
public:
	GameOptions();
	~GameOptions();
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
};

#endif