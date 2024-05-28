#include "Settings.h"
#include "Menu.h"

Settings::Settings(StateManager& stateManager) : StateScreen(stateManager)
{
	using namespace sf;
	text.setFont(getAssetManager()->getFont("game font"));
	text.setFillColor(Color::White);
}

Settings::~Settings()
{
}

void Settings::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
	using namespace std;
	if (event.type != Event::KeyPressed) return;
	Keyboard::Key key = event.key.code;
	if (isChanging)
	{
		changeKey(key);
		return;
	}
	ofstream outFile;
	switch (key)
	{
	case Keyboard::Key::Escape:
		GameSettings::getInstance()->saveKeys();
		GameSettings::getInstance()->saveConfig();
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		break;
	case Keyboard::Key::Down:
		setCursor(cursor + 1);
		break;
	case Keyboard::Key::Up:
		setCursor(cursor - 1);
		break;
	case Keyboard::Key::Return:
		isChanging = true;
		break;
	}
}

void Settings::tick(const float & dt, sf::RenderWindow& window)
{
}

void Settings::render(sf::RenderWindow& window)
{
	using namespace sf;
	using namespace std;
	text.setFillColor(Color::White);
	text.setCharacterSize(120);
	text.setString("Change key config");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 50);
	window.draw(text);

	for (int i = 0; i < int(Controls_Key::SIZE); i++)
	{
		Controls_Key key = static_cast<Controls_Key> (i);
		drawKeyConfig(fromControlsToString(key), fromKtoS(settings->keybinds[key]), 500, 300 + 80 * i, window, cursor == i, isChanging);
	}


	drawKeyConfig("SFX", "<  " + to_string(settings->sfx) + "  >", 500, 300 + 80 * int(Controls_Key::SIZE), window, cursor == int(Controls_Key::SIZE), isChanging);
	drawKeyConfig("MUSIC", "<  " + to_string(settings->music) + "  >", 500, 300 + 80 * (int(Controls_Key::SIZE) + 1), window, cursor == (int(Controls_Key::SIZE) + 1), isChanging);

	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(getAssetManager()->getDrawable("back button hl"));
	}
	else
	{
		window.draw(getAssetManager()->getDrawable("back button"));
	}
}

void Settings::drawKeyConfig(std::string name, std::string key, int x, int y, sf::RenderWindow& window, bool isHighlight, bool changing)
{
	using namespace sf;
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(1000, 50));
		rect.setPosition(x, y);
		rect.setFillColor(Color::White);
		window.draw(rect);
		if (changing)
		{
			RectangleShape rect(Vector2f(300, 50));
			rect.setPosition(x + 700, y);
			rect.setFillColor(Color::Red);
			window.draw(rect);
		}

		text.setFillColor(Color::Black);

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y-15);
	text.setCharacterSize(60);
	text.setString(name);
	window.draw(text);

	text.setPosition(x + 750, y-15);
	text.setString(key);
	window.draw(text);
}

bool Settings::changeKey(sf::Keyboard::Key key)
{
	using namespace sf;
	using namespace std;
	// dismiss special keys
	if (key == Keyboard::Key::Escape || key == Keyboard::Key::Unknown || key == Keyboard::Key::R) return false;

	if (cursor == 3)
	{
		if (key == Keyboard::Key::Right)
		{
			settings->sfx = clamp(settings->sfx + 1, 0, 100);
			return true;
		}
		else if (key == Keyboard::Key::Left)
		{
			settings->sfx = clamp(settings->sfx - 1, 0, 100);
			return true;
		}
		else if (key == Keyboard::Key::Return)
		{
			isChanging = false;
			return true;
		}
		return false;
	}
	else if (cursor == 4)
	{
		if (key == Keyboard::Key::Right)
		{
			settings->music = clamp(settings->music + 1, 0, 100);
			return true;
		}
		else if (key == Keyboard::Key::Left)
		{
			settings->music = clamp(settings->music - 1, 0, 100);
			return true;
		}
		else if (key == Keyboard::Key::Return)
		{
			isChanging = false;
			return true;
		}
		return false;
	}

	settings->keybinds[Controls_Key(cursor)] = key;
	isChanging = false;
	return true;
}


void Settings::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		GameSettings::getInstance()->saveKeys();
		GameSettings::getInstance()->saveConfig();
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
	}
}

void Settings::setCursor(int cursor)
{
	// clamping from 0 to 9
	this->cursor = std::clamp(cursor, 0, int(Controls_Key::SIZE) - 1 + 2); // + 2 for the SFX + MUSIC option
}

// TODO: Handle invalid input
std::string Settings::fromControlsToString(Controls_Key key)
{
	return controlsStringMap.at(key);
}

// TODO: Handle invalid input
std::string Settings::fromKtoS(const sf::Keyboard::Key& k)
{
	return keyboardKeyStringMap.at(k);
}