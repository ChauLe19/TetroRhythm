#ifndef MASTER_CLASS_H
#define MASTER_CLASS_H

#include <SFML/Graphics.hpp>
#include "KeyInput.h"
#include "Game.h"
class MasterClass
{
private:
	Game* game;
	KeyInput* keyInput;
	RenderWindow* window; 
	Clock clock;
	Font font;
	Text text;
public:
	int frameCount = 0;
	MasterClass();
	MasterClass(RenderWindow& window);
	~MasterClass();
	void render(RenderWindow& window);
	void tick(RenderWindow& window);
	void run();
	void render();
	void tick();
};

#endif