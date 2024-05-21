#include "Menu.h"
#include "Tutorial.h"

Menu::Menu(StateManager &stateManager) : StateScreen(stateManager)
{
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(sf::Color::White);
}

Menu::~Menu()
{
}

void Menu::tick(const float & dt, sf::RenderWindow& window)
{
}

void Menu::render(sf::RenderWindow& window)
{
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setString("TetroRhythm");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 100);
	window.draw(text);


	beginButton.render(window, text);
	settingsButton.render(window, text);
	beatmapButton.render(window, text);
	tutorialButton.render(window, text);
	exitButton.render(window, text);
}

void Menu::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
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

void Menu::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
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
		else if (tutorialButton.mouseInButton(window)) // tutorial button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Tutorial(stateManager)));
		}
		else if (exitButton.mouseInButton(window)) // exit button
		{
			window.close();
		}
	}
	else if (event.type == Event::MouseMoved)
	{
		beginButton.setHighlight(beginButton.mouseInButton(window));
		settingsButton.setHighlight(settingsButton.mouseInButton(window));
		beatmapButton.setHighlight(beatmapButton.mouseInButton(window));
		tutorialButton.setHighlight(tutorialButton.mouseInButton(window));
		exitButton.setHighlight(exitButton.mouseInButton(window));
	}
}
