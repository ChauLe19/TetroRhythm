#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Menu
{
private:
	Text text;
	Font font;
public:
	Menu();
	~Menu();
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
};
#endif
