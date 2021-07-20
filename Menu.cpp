#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
}

Menu::~Menu()
{
}

void Menu::tick(RenderWindow& window)
{
}

void Menu::render(RenderWindow& window)
{
	text.setPosition(300, 300);
	text.setCharacterSize(30);
	text.setString("TetroRythm");
	window.draw(text);

	text.setPosition(250, 400);
	text.setCharacterSize(20);
	text.setString("Press Enter to begin");
	window.draw(text);
}
