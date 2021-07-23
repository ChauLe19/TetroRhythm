#ifndef MASTER_CLASS_H
#define MASTER_CLASS_H

#include <SFML/Graphics.hpp>
#include "KeyInput.h"
#include "GameBase.h"
#include "Menu.h"
#include "Settings.h"
#include "Enums.h"
#include "GameOptions.h"

class MasterClass
{
private:
	State state = State::MENU;
	Menu* menu;
	GameBase* game;
	KeyInput* keyInput;
	Settings* settings;
	RenderWindow* window;
	GameOptions* gameOptions;
	Clock clock;
	Font font;
	Text text;
	int delayAutoShiftMS = 100; //ms  
	int delayAutoShift = (int)((float)delayAutoShiftMS / 1000 * 60); // frame // delayAutoShiftMS/1000 * 60  
	int autoRepeatRate = 0; // frame
	array<Keyboard::Key, 8> keyMap = { Keyboard::Key::J, Keyboard::Key::L, Keyboard::Key::A, Keyboard::Key::F,
	Keyboard::Key::S, Keyboard::Key::D, Keyboard::Key::I, Keyboard::Key::K };
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
	void keyEvent(Keyboard::Key key);
};

#endif