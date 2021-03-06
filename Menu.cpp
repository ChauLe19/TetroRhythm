#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("Dense-Regular.otf");
	text.setFont(font);
	text.setFillColor(Color::White);

	buttonTexture.loadFromFile("Images/button.png");
	buttonImage.setTexture(buttonTexture);
}

Menu::~Menu()
{
}

void Menu::tick(State& state, RenderWindow& window)
{
}

void Menu::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setCharacterSize(200);
	text.setString("TetroRhythm");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 200);
	window.draw(text);


	createButton(window, text, Color(0, 0, 50, 255), 60, Color::White, "BEGIN (Enter)", 400, 60, 1024 - 200, 600);
	createButton(window, text, Color(0, 0, 50, 255), 60, Color::White, "SETTINGS (C)", 400, 60, 1024 - 200, 700);
	createButton(window, text, Color(0, 0, 50, 255), 60, Color::White, "EDIT BEAT MAPS (E)", 400, 60, 1024 - 200, 800);

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

void Menu::mouseEvent(State& state, RenderWindow& window)
{
	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		firstPressed = true;
		return;
	}
	if (firstPressed && mouseInBox(window, 1024 - 200, 600, 400, 60)) // BEGIN button
	{
		state = State::GAME_OPTIONS;
	}
	else if (firstPressed && mouseInBox(window, 1024 - 200, 700, 400, 60)) //SETTINGS button
	{
		state = State::SETTINGS;
	}
	else if (firstPressed && mouseInBox(window, 1024 - 200, 800, 400, 60)) // EDIT BEAT MAPS button
	{
		state = State::MAP_EDITOR_SELECT;
	}
	firstPressed = false;

}
