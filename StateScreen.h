#ifndef STATE_SCREEN_H
#define STATE_SCREEN_H

#include <SFML/Graphics.hpp>
#include "Enums.h"
using namespace sf;
class StateScreen
{
public:
	virtual void tick(RenderWindow& window) = 0;
	virtual void render(RenderWindow& window) = 0;
	virtual void keyEvent(State& state, Keyboard::Key key) = 0;
};

#endif