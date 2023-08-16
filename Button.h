#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Button
{
private:
	int x;
	int y;
	int width;
	int height;
	int fontSize;
	string textString;
	sf::Color boxColor;
	sf::Color textColor;
	Keyboard::Key key;
public:
	Button(Color textColor, int fontSize, sf::Color boxColor, string textString, int x, int y, int width, int height, Keyboard::Key key);
	~Button();
	//void doFunc(void (*function)());
	bool keyEvent(Keyboard::Key key);
	void render(RenderWindow& window, Text& text);
	bool mouseInButton(RenderWindow& window);

};
#endif
