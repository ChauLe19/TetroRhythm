#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Button
{
private:
	Vector2f position;
	Vector2f size;
	int fontSize;
	bool isHighlight;
	string textString;
	sf::Color boxColor;
	sf::Color textColor;
	sf::Color highlightColor;

	RectangleShape buttonRect;
	Keyboard::Key key;
public:
	Button(Color textColor, int fontSize, sf::Color boxColor, string textString, Vector2f position, Vector2f size, sf::Color highlightColor = Color::White, Keyboard::Key key = Keyboard::Unknown);
	~Button();
	void setHighlight(bool isHighlight);
	bool keyEvent(Keyboard::Key key);
	void render(RenderWindow& window, Text& text);
	bool mouseInButton(RenderWindow& window);

};
#endif
