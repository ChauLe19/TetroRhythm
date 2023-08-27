#include "Menu.h"

Menu::Menu(StateManager &stateManager) : StateScreen(stateManager)
{
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);

	buttonImage.setTexture(assetManager->getTexture("button"));
}

Menu::~Menu()
{
}

void Menu::tick(const float & dt, RenderWindow& window)
{
}

void Menu::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setCharacterSize(200);
	text.setString("TetroRhythm");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 200);
	window.draw(text);


	beginButton.render(window, text);
	settingsButton.render(window, text);
	beatmapButton.render(window, text);

}

void Menu::keyEvent(const float & dt, Event event)
{
	if (event.type != Event::KeyPressed) return;
	switch (event.key.code)
	{
	case Keyboard::Key::Return:
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

void Menu::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (beginButton.mouseInButton(window)) // BEGIN button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new GameOptions(stateManager)));
		}
		else if (settingsButton.mouseInButton(window)) //SETTINGS button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Settings(stateManager)));
		}
		else if (beatmapButton.mouseInButton(window)) // EDIT BEAT MAPS button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new MapEditorSelect(stateManager)));
		}
	}
	else if (event.type == Event::MouseMoved)
	{
		beginButton.setHighlight(false);
		settingsButton.setHighlight(false);
		beatmapButton.setHighlight(false);

		if (beginButton.mouseInButton(window)) // BEGIN button
		{
			beginButton.setHighlight(true);
		}
		else if (settingsButton.mouseInButton(window)) //SETTINGS button
		{
			settingsButton.setHighlight(true);
		}
		else if (beatmapButton.mouseInButton(window)) // EDIT BEAT MAPS button
		{
			beatmapButton.setHighlight(true);
		}
	}
}
