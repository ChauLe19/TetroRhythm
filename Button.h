#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Button : public sf::Drawable
{
protected:
	bool isHighlight;
	sf::Color boxColor;
	sf::Color highlightColor;
	sf::Color baseColor;
	sf::Text text;

	sf::RectangleShape buttonRect;
	sf::Keyboard::Key key;
public:
	Button();
	Button(sf::RectangleShape buttonRect, sf::Text text, sf::Color baseColor, sf::Color highlightColor);
	Button(sf::Color textColor, int fontSize, sf::Color boxColor, std::string textString, sf::Vector2f position, sf::Vector2f size, sf::Color highlightColor = sf::Color::White, sf::Keyboard::Key key = sf::Keyboard::Unknown);
	~Button();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setFont(sf::Font& font);
	void setFontSize(int fontSize);
	void setTextString(std::string textString);
	void recomputePosition();
	void setHighlightColor(const sf::Color& color);
	void setBaseColor(const sf::Color& color);
	void setColor(const sf::Color& baseColor, const sf::Color& highlightColor);
	void setHighlight(bool isHighlight);
	bool isHighlighted();
	bool keyEvent(sf::Keyboard::Key key);
	bool mouseInButton(sf::RenderWindow& window);
	bool posInButton(int x, int y);


	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

};
#endif
