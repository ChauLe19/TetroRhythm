#ifndef SETTINGS_H
#define SETTINGS_H

#include "StateScreen.h"
#include <SFML/Graphics.hpp>
#include <array>
#include "Enums.h"
using namespace sf;
using namespace std;
class Settings : public StateScreen
{
private:
	Text text;
	Font font; 
	int& delayAutoShift; // frame // delayAutoShiftMS/1000 * 60  
	int& autoRepeatRate; // frame
	array<Keyboard::Key, 8>& keyMap;
	int cursor = 0;
	bool isChanging = false;
	string fromKtoS(const sf::Keyboard::Key& k);
	string fromControlsToString(Controls_Key key);
public:
	//Settings(); 
	Settings(array<Keyboard::Key, 8>& keyMap, int& delayAutoShift, int& autoRepeatRate);
	~Settings();
	void keyEvent(State & state, Keyboard::Key key);
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void render(RenderWindow& window, array<Keyboard::Key, 8>& keyMap, int delayAutoShift, int autoRepeatRate);
	void drawKeyConfig(string name, string key, int x, int y, RenderWindow& window, bool isHighlight, bool changing);
	void drawKeyConfig(string name, string key, int x, int y, RenderWindow& window, bool isHighlight);
	void waitForChangingKey();
	bool getIsChanging();
	bool changeKey(Keyboard::Key key, array<Keyboard::Key, 8>& keyMap, int& delayAutoShift, int& autoRepeatRate);
	bool changeKey(Keyboard::Key key, array<Keyboard::Key, 8>& keyMap);
	int getCursor();
	void setCursor(int cursor);
};
#endif

