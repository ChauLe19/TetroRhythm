#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Enums.h"
using namespace sf;
enum class Controls_Key {
	MOVE_LEFT = 0, MOVE_RIGHT, ROTATE_CCW, ROTATE_CW,
	ROTATE_180, HOLD, HARD_DROP, SOFT_DROP
};
class KeyInput : public Keyboard
{
private:
	int delayAutoShiftMS = 100; //ms  
	int delayAutoShift = (int)((float)delayAutoShiftMS / 1000 * 60); // frame // delayAutoShiftMS/1000 * 60  
	int autoRepeatRate = 0; // frame
	int delayAutoShiftCount = 0;
	int autoRepeatRateCount = 0;
	Keyboard::Key holdKey;
	Keyboard::Key currentKey;
	bool isAutoShiftActive = false;
	bool isAutoRepeatActive = false;
	bool firstPressed = false;
	Keyboard::Key moveRightKey = Key::J;
	Keyboard::Key keyMap[8] = { Key::J, Key::L, Key::A, Key::F,
		Key::S, Key::D, Key::I, Key::K};

public:
	KeyInput();
	//KeyInput(Game& game);
	~KeyInput();
	void tick(State& state, Game& game);
	void updateKeyEvent(State& state, Keyboard::Key key);
	void noHoldKeyEvent(State& state, Keyboard::Key key, Game& game);
};
#endif
