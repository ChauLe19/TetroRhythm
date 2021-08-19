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

void createButton(RenderWindow& window,Text &text, Color textColor, Color boxColor, string textString, int width, int height, int x, int y)
{
	RectangleShape rect;
	rect.setSize(Vector2f(width, height));
	rect.setFillColor(Color(boxColor.r-100, boxColor.g-100, boxColor.b-100, 255));
	rect.setPosition(Vector2f(x,y+10));
	window.draw(rect);

	rect.setFillColor(boxColor);
	rect.setSize(Vector2f(width, height));
	rect.setPosition(Vector2f(x,y));
	window.draw(rect);


	text.setFillColor(textColor);
	//text.setPosition(1024-60, 595);
	text.setCharacterSize(60);
	text.setString(textString);
	text.setPosition(1024 - text.getLocalBounds().width / 2, y-10);
	window.draw(text);
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
}
