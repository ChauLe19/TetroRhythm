#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Button
{
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	int fontSize;
	bool isHighlight;
	std::string textString;
	sf::Color boxColor;
	sf::Color textColor;
	sf::Color highlightColor;

	sf::RectangleShape buttonRect;
	sf::Keyboard::Key key;
public:
	Button(sf::Color textColor, int fontSize, sf::Color boxColor, std::string textString, sf::Vector2f position, sf::Vector2f size, sf::Color highlightColor = sf::Color::White, sf::Keyboard::Key key = sf::Keyboard::Unknown);
	~Button();
	void setHighlight(bool isHighlight);
	bool isHighlighted();
	bool keyEvent(sf::Keyboard::Key key);
	void render(sf::RenderWindow& window, sf::Text& text);
	bool mouseInButton(sf::RenderWindow& window);
	bool posInButton(int x, int y);

};
#endif
