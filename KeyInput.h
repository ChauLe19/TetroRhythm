#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace sf;

class KeyInput : public Keyboard
{
private:
	int delayAutoShiftMS = 100; //ms  
	int delayAutoShift = (int)((float)delayAutoShiftMS/1000 * 60); // frame // delayAutoShiftMS/1000 * 60  
	int autoRepeatRate = 0; // frame
	int delayAutoShiftCount = 0;
	int autoRepeatRateCount = 0;
	Keyboard::Key holdKey;
	bool isAutoShiftActive = false;
	bool isAutoRepeatActive = false;
	bool firstPressed = false;
	Keyboard::Key currentKey;
public:
	KeyInput();
	//KeyInput(Game& game);
	~KeyInput();
	void tick(Game& game);
	void updateKeyEvent(Keyboard::Key key);
	void noHoldKeyEvent(Keyboard::Key key, Game &game);
};
#endif
