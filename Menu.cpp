#include "Menu.h"

Menu::Menu(StateManager &stateManager) : StateScreen(stateManager)
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

void Menu::tick(RenderWindow& window)
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

void Menu::keyEvent(Event event)
{
	if (event.type != Event::KeyPressed) return;
	switch (event.key.code)
	{
	case Keyboard::Key::Enter:
		stateManager.addState(std::unique_ptr<StateScreen>(new GameOptions(stateManager)));
		break;
	case Keyboard::Key::C:
		stateManager.addState(std::unique_ptr<StateScreen>(new Settings(stateManager)));
		break;
	case Keyboard::Key::E:
		stateManager.addState(std::unique_ptr<StateScreen>(new MapEditorSelect(stateManager)));
		break;
	}
}

void Menu::mouseEvent(RenderWindow& window, Event event)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (mouseInBox(window, 1024 - 200, 600, 400, 60)) // BEGIN button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new GameOptions(stateManager)));
		}
		else if ( mouseInBox(window, 1024 - 200, 700, 400, 60)) //SETTINGS button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Settings(stateManager)));
		}
		else if (mouseInBox(window, 1024 - 200, 800, 400, 60)) // EDIT BEAT MAPS button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new MapEditorSelect(stateManager)));
		}
	}
}
