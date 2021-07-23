#ifndef MENU_H
#define MENU_H

#include "StateScreen.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu : public StateScreen
{
private:
	Text text;
	Font font;
public:
	Menu();
	~Menu();
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(State& state, Keyboard::Key key);
};
#endif
