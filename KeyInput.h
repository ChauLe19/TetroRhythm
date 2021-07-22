#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <SFML/Graphics.hpp>
#include "GameBase.h"
#include "DropToTheBeatGame.h"
#include "AutoDropGame.h"
#include "Settings.h"
#include "Enums.h"
using namespace sf;

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
	array<Keyboard::Key,8> keyMap = { Key::J, Key::L, Key::A, Key::F,
		Key::S, Key::D, Key::I, Key::K};

public:
	KeyInput();
	//KeyInput(Game& game);
	~KeyInput();
	void tick(State& state, GameBase& game);
	void updateKeyEvent(State& state, Keyboard::Key key);
	void noHoldKeyEvent(State& state, Keyboard::Key key, GameBase& game, Settings& settings);
	array<Keyboard::Key, 8>& getKeyMap();
	int getDelayAutoShift();
	int getAutoRepeatRate();
};
#endif
