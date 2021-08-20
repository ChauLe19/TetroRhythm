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
	text.setString("TetroRythm");
	text.setPosition(1024-text.getLocalBounds().width/2, 200);
	window.draw(text);


	createButton(window, text, Color(0, 0, 50, 255), Color::White, "BEGIN", 400, 60, 1024 - 200, 600);
	createButton(window, text, Color(0, 0, 50, 255), Color::White, "SETTINGS", 400, 60, 1024 - 200, 700);
	createButton(window, text, Color(0, 0, 50, 255), Color::White, "EDIT BEAT MAPS", 400, 60, 1024 - 200, 800);

	//RectangleShape rect;
	//rect.setSize(Vector2f(400, 60));
	//rect.setFillColor(Color(150, 150, 150, 255));
	//rect.setPosition(Vector2f(1024 - 200, 600));
	//window.draw(rect);

	//rect.setFillColor(Color::White);
	//rect.setSize(Vector2f(400,60));
	//rect.setPosition(Vector2f(1024-200, 590));
	//window.draw(rect);
	//

	//text.setFillColor(Color::Black);
	////text.setPosition(1024-60, 595);
	//text.setCharacterSize(40);
	//text.setString("BEGIN");
	//text.setPosition(1024 - text.getLocalBounds().width / 2, 595);
	//window.draw(text);


	//rect.setSize(Vector2f(400, 60));
	//rect.setFillColor(Color(150, 150, 150, 255));
	//rect.setPosition(Vector2f(1024 - 200, 700));
	//window.draw(rect);

	//rect.setFillColor(Color::White);
	//rect.setSize(Vector2f(400, 60));
	//rect.setPosition(Vector2f(1024 - 200, 690));
	//window.draw(rect);

	//text.setFillColor(Color::Black);
	////text.setPosition(930, 695);
	//text.setCharacterSize(40);
	//text.setString("SETTINGS");
	//text.setPosition(1024 - text.getLocalBounds().width / 2, 695);
	//text.getLocalBounds().width;
	//window.draw(text);
	//

	//rect.setSize(Vector2f(400, 60));
	//rect.setFillColor(Color(150, 150, 150, 255));
	//rect.setPosition(Vector2f(1024 - 200, 800));
	//window.draw(rect);

	//rect.setFillColor(Color::White);
	//rect.setSize(Vector2f(400, 60));
	//rect.setPosition(Vector2f(1024 - 200, 790));
	//window.draw(rect);

	////text.setPosition(860, 795);
	//text.setCharacterSize(40);
	//text.setString("EDIT BEAT MAPS");
	//text.setPosition(1024 - text.getLocalBounds().width / 2, 795);
	//window.draw(text);
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
