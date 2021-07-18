#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <SFML/Graphics.hpp>
using namespace sf;

class KeyInput : public Keyboard
{
private:
	int delayAutoShiftMS = 100; //ms  
	int delayAutoShift = 10000;/*(int)((float)delayAutoShiftMS/1000 * 60);*/// frame // delayAutoShiftMS/1000 * 60  
	int autoRepeatRate = 1; // frame
	int delayAutoShiftCount = 0;
	int autoRepeatRateCount = 0;
	Keyboard::Key holdKey;
	bool isAutoShiftActive = false;
	bool isAutoRepeatActive = false;
public:
};
#endif
