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
	text.setPosition(650, 200);
	text.setCharacterSize(150);
	text.setString("TetroRythm");
	window.draw(text);


	text.setPosition(900, 600);
	text.setCharacterSize(40);
	text.setString("Enter to begin");
	window.draw(text);

	text.setPosition(830, 650);
	text.setCharacterSize(40);
	text.setString("C to edit configuration");
	window.draw(text);
	
	text.setPosition(850, 700);
	text.setCharacterSize(40);
	text.setString("E to edit beat maps");
	window.draw(text);
}

void Menu::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Enter:
		state = State::GAME_OPTIONS;
		break;
	case Keyboard::Key::C:
		state = State::SETTINGS;
		break;
	case Keyboard::Key::E:
		state = State::MAP_EDITOR_SELECT;
		break;
	}
}

void Menu::mouseEvent(RenderWindow& window)
{
}
