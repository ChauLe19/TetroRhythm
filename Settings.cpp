#include "Settings.h"
#include "Menu.h"

Settings::Settings(StateManager& stateManager) : StateScreen(stateManager)
{
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);
}

Settings::~Settings()
{
}

void Settings::keyEvent(Event event)
{
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
		outFile.open("Config/Keybinds.txt", ios::out);
		for (std::map<string, Keyboard::Key>::iterator it = settings.keybinds.begin(); it != settings.keybinds.end(); ++it)
		{
			outFile << it->first << ' ' << it->second << endl;
		}
		outFile.close();
		outFile.open("Config/Config.txt", ios::out);
		outFile << "DAS " << settings.delayAutoShift << endl;
		outFile << "ARR " << settings.autoRepeatRate << endl;
		outFile.close();
		// state = State::MENU;
		GameSettings::loadFiles(); // reload settings
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

void Settings::tick(RenderWindow& window)
{
}

void Settings::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setCharacterSize(120);
	text.setString("Change key config");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 50);
	window.draw(text);

	for (int i = 0; i < 8; i++)
	{
		Controls_Key key = static_cast<Controls_Key> (i);
		drawKeyConfig(fromControlsToString(key), fromKtoS(settings.keybinds[controlsList[i]]), 500, 300 + 80 * i, window, cursor == i, isChanging);
	}


	drawKeyConfig("DAS", "<  " + to_string(settings.delayAutoShift) + "  >", 500, 300 + 80 * 8, window, cursor == 8, isChanging);
	drawKeyConfig("ARR", "<  " + to_string(settings.autoRepeatRate) + "  >", 500, 300 + 80 * 9, window, cursor == 9, isChanging);
}

void Settings::drawKeyConfig(string name, string key, int x, int y, RenderWindow& window, bool isHighlight, bool changing)
{
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

	text.setPosition(x + 825, y-15);
	text.setString(key);
	window.draw(text);
}

bool Settings::changeKey(Keyboard::Key key)
{
	// dismiss special keys
	if (key == Keyboard::Key::Escape || key == Keyboard::Key::Unknown || key == Keyboard::Key::R) return false;

	if (cursor == 8)
	{
		if (key == Keyboard::Key::Right)
		{
			settings.delayAutoShift++;
			return true;
		}
		else if (key == Keyboard::Key::Left)
		{
			settings.delayAutoShift--;
			return true;
		}
		else if (key == Keyboard::Key::Return)
		{
			isChanging = false;
			return true;
		}
		return false;
	}
	else if (cursor == 9)
	{
		if (key == Keyboard::Key::Right)
		{
			settings.autoRepeatRate++;
			return true;
		}
		else if (key == Keyboard::Key::Left)
		{
			settings.autoRepeatRate--;
			return true;
		}
		else if (key == Keyboard::Key::Return)
		{
			isChanging = false;
			return true;
		}
		return false;
	}

	settings.keybinds[controlsList[cursor]] = key;
	isChanging = false;
	return true;
}


void Settings::mouseEvent(RenderWindow& window, Event event)
{
}

void Settings::setCursor(int cursor)
{
	// clamping from 0 to 9
	this->cursor = cursor < 0 ? 0 : cursor >9 ? 9 : cursor;
}

// TODO: Handle invalid input
string Settings::fromControlsToString(Controls_Key key)
{
	return controlsStringMap.at(key);
}

// TODO: Handle invalid input
string Settings::fromKtoS(const sf::Keyboard::Key& k)
{
	return keyboardKeyStringMap.at(k);
}