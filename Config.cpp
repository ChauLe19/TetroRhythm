#include "Config.h"

Config::Config()
{
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
}

Config::~Config()
{
}

void Config::tick(RenderWindow& window)
{
}

void Config::render(RenderWindow& window, array<Keyboard::Key, 8>& keyMap)
{
	text.setFillColor(Color::White);
	text.setPosition(100, 100);
	text.setCharacterSize(30);
	text.setString("Change key config");
	window.draw(text);


	for (int i = 0; i < keyMap.size(); i++)
	{
		Controls_Key key = static_cast<Controls_Key> (i);
		drawKeyConfig(fromControlsToString(key), fromKtoS(keyMap[i]), 50, 150 + 50 * i, window, cursor == i, isChanging);
	}
}

void Config::drawKeyConfig(string name, string key, int x, int y, RenderWindow& window, bool isHighlight, bool changing)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(300, 25));
		rect.setPosition(x, y);
		rect.setFillColor(Color::Yellow);
		window.draw(rect);
		if (changing)
		{
			RectangleShape rect(Vector2f(100, 25));
			rect.setPosition(x+200, y);
			rect.setFillColor(Color::Red);
			window.draw(rect);
		}

		text.setFillColor(Color::Black);

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y);
	text.setCharacterSize(20);
	text.setString(name);
	window.draw(text);

	text.setPosition(x + 225, y);
	text.setString(key);
	window.draw(text);
}

void Config::waitForChangingKey()
{
	isChanging = true;
}

bool Config::getIsChanging()
{
	return isChanging;
}

bool Config::changeKey(Keyboard::Key key, array<Keyboard::Key, 8>& keyMap)
{
	// dismiss special keys
	if (key == Keyboard::Key::Escape || key == Keyboard::Key::Unknown || key == Keyboard::Key::R) return false;

	keyMap[cursor] = key;
	isChanging = false;
	return true;
}

int Config::getCursor()
{
	return cursor;
}

void Config::setCursor(int cursor)
{
	// clamping from 0 to 7
	this->cursor = cursor < 0 ? 0 : cursor >7 ? 7 : cursor;
}

string Config::fromControlsToString(Controls_Key key)
{
	switch (key)
	{
	case Controls_Key::MOVE_LEFT:
		return "Move left";
	case Controls_Key::MOVE_RIGHT:
		return "Move right";
	case Controls_Key::ROTATE_CCW:
		return "Rotate CCW";
	case Controls_Key::ROTATE_CW:
		return "Rotate CW";
	case Controls_Key::ROTATE_180:
		return "Rotate 180";
	case Controls_Key::HOLD:
		return "Hold";
	case Controls_Key::HARD_DROP:
		return "Hard drop";
	case Controls_Key::SOFT_DROP:
		return "Soft drop";
	}
}

string Config::fromKtoS(const sf::Keyboard::Key& k) {
	string ret;
	switch (k) {
	case sf::Keyboard::A:
		ret = "A";
		break;
	case sf::Keyboard::B:
		ret = "B";
		break;
	case sf::Keyboard::C:
		ret = "C";
		break;
	case sf::Keyboard::D:
		ret = "D";
		break;
	case sf::Keyboard::E:
		ret = "E";
		break;
	case sf::Keyboard::F:
		ret = "F";
		break;
	case sf::Keyboard::G:
		ret = "G";
		break;
	case sf::Keyboard::H:
		ret = "H";
		break;
	case sf::Keyboard::I:
		ret = "I";
		break;
	case sf::Keyboard::J:
		ret = "J";
		break;
	case sf::Keyboard::K:
		ret = "K";
		break;
	case sf::Keyboard::L:
		ret = "L";
		break;
	case sf::Keyboard::M:
		ret = "M";
		break;
	case sf::Keyboard::N:
		ret = "N";
		break;
	case sf::Keyboard::O:
		ret = "O";
		break;
	case sf::Keyboard::P:
		ret = "P";
		break;
	case sf::Keyboard::Q:
		ret = "Q";
		break;
	case sf::Keyboard::R:
		ret = "R";
		break;
	case sf::Keyboard::S:
		ret = "S";
		break;
	case sf::Keyboard::T:
		ret = "T";
		break;
	case sf::Keyboard::U:
		ret = "U";
		break;
	case sf::Keyboard::V:
		ret = "V";
		break;
	case sf::Keyboard::W:
		ret = "W";
		break;
	case sf::Keyboard::X:
		ret = "X";
		break;
	case sf::Keyboard::Y:
		ret = "Y";
		break;
	case sf::Keyboard::Z:
		ret = "Z";
		break;
	case sf::Keyboard::Num0:
		ret = "Num0";
		break;
	case sf::Keyboard::Num1:
		ret = "Num1";
		break;
	case sf::Keyboard::Num2:
		ret = "Num2";
		break;
	case sf::Keyboard::Num3:
		ret = "Num3";
		break;
	case sf::Keyboard::Num4:
		ret = "Num4";
		break;
	case sf::Keyboard::Num5:
		ret = "Num5";
		break;
	case sf::Keyboard::Num6:
		ret = "Num6";
		break;
	case sf::Keyboard::Num7:
		ret = "Num7";
		break;
	case sf::Keyboard::Num8:
		ret = "Num8";
		break;
	case sf::Keyboard::Num9:
		ret = "Num9";
		break;
	case sf::Keyboard::Escape:
		ret = "Escape";
		break;
	case sf::Keyboard::LControl:
		ret = "LControl";
		break;
	case sf::Keyboard::LShift:
		ret = "LShift";
		break;
	case sf::Keyboard::LAlt:
		ret = "LAlt";
		break;
	case sf::Keyboard::LSystem:
		ret = "LSystem";
		break;
	case sf::Keyboard::RControl:
		ret = "RControl";
		break;
	case sf::Keyboard::RShift:
		ret = "RShift";
		break;
	case sf::Keyboard::RAlt:
		ret = "RAlt";
		break;
	case sf::Keyboard::RSystem:
		ret = "RSystem";
		break;
	case sf::Keyboard::Menu:
		ret = "Menu";
		break;
	case sf::Keyboard::LBracket:
		ret = "LBracket";
		break;
	case sf::Keyboard::RBracket:
		ret = "RBracket";
		break;
	case sf::Keyboard::SemiColon:
		ret = "SemiColon";
		break;
	case sf::Keyboard::Comma:
		ret = "Comma";
		break;
	case sf::Keyboard::Period:
		ret = "Period";
		break;
	case sf::Keyboard::Quote:
		ret = "Quote";
		break;
	case sf::Keyboard::Slash:
		ret = "Slash";
		break;
	case sf::Keyboard::BackSlash:
		ret = "BackSlash";
		break;
	case sf::Keyboard::Tilde:
		ret = "Tilde";
		break;
	case sf::Keyboard::Equal:
		ret = "Equal";
		break;
	case sf::Keyboard::Dash:
		ret = "Dash";
		break;
	case sf::Keyboard::Space:
		ret = "Space";
		break;
	case sf::Keyboard::Return:
		ret = "Return";
		break;
	case sf::Keyboard::BackSpace:
		ret = "BackSpace";
		break;
	case sf::Keyboard::Tab:
		ret = "Tab";
		break;
	case sf::Keyboard::PageUp:
		ret = "PageUp";
		break;
	case sf::Keyboard::PageDown:
		ret = "PageDown";
		break;
	case sf::Keyboard::End:
		ret = "End";
		break;
	case sf::Keyboard::Home:
		ret = "Home";
		break;
	case sf::Keyboard::Insert:
		ret = "Insert";
		break;
	case sf::Keyboard::Delete:

		ret = "Delete";
		break;
	case sf::Keyboard::Add:
		ret = "Add";
		break;
	case sf::Keyboard::Subtract:
		ret = "Subtract";
		break;
	case sf::Keyboard::Multiply:
		ret = "Multiply";
		break;
	case sf::Keyboard::Divide:
		ret = "Divide";
		break;
	case sf::Keyboard::Left:
		ret = "Left";
		break;
	case sf::Keyboard::Right:
		ret = "Right";
		break;
	case sf::Keyboard::Up:
		ret = "Up";
		break;
	case sf::Keyboard::Down:
		ret = "Down";
		break;
	case sf::Keyboard::Numpad0:
		ret = "Numpad0";
		break;
	case sf::Keyboard::Numpad1:
		ret = "Numpad1";
		break;
	case sf::Keyboard::Numpad2:
		ret = "Numpad2";
		break;
	case sf::Keyboard::Numpad3:
		ret = "Numpad3";
		break;
	case sf::Keyboard::Numpad4:
		ret = "Numpad4";
		break;
	case sf::Keyboard::Numpad5:
		ret = "Numpad5";
		break;
	case sf::Keyboard::Numpad6:
		ret = "Numpad6";
		break;
	case sf::Keyboard::Numpad7:
		ret = "Numpad7";
		break;
	case sf::Keyboard::Numpad8:
		ret = "Numpad8";
		break;
	case sf::Keyboard::Numpad9:
		ret = "Numpad9";
		break;
	case sf::Keyboard::F1:
		ret = "F1";
		break;
	case sf::Keyboard::F2:
		ret = "F2";
		break;
	case sf::Keyboard::F3:
		ret = "F3";
		break;
	case sf::Keyboard::F4:
		ret = "F4";
		break;
	case sf::Keyboard::F5:
		ret = "F5";
		break;
	case sf::Keyboard::F6:
		ret = "F6";
		break;
	case sf::Keyboard::F7:
		ret = "F7";
		break;
	case sf::Keyboard::F8:
		ret = "F8";
		break;
	case sf::Keyboard::F9:
		ret = "F9";
		break;
	case sf::Keyboard::F10:
		ret = "F10";
		break;
	case sf::Keyboard::F11:
		ret = "F11";
		break;
	case sf::Keyboard::F12:
		ret = "F12";
		break;
	case sf::Keyboard::F13:
		ret = "F13";
		break;
	case sf::Keyboard::F14:
		ret = "F14";
		break;
	case sf::Keyboard::F15:
		ret = "F15";
		break;
	case sf::Keyboard::Pause:
		ret = "Pause";
		break;
	case sf::Keyboard::KeyCount:
		ret = "KeyCount";
		break;
	default:
		ret = "Unknow";
		break;
	}
	return ret;
}