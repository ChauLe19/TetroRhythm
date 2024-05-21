#include "Button.h"

Button::Button(sf::Color textColor, int fontSize, sf::Color boxColor, std::string textString, sf::Vector2f position, sf::Vector2f size, sf::Color highlightColor, sf::Keyboard::Key key)
{
	this->textColor = textColor;
	this->fontSize = fontSize;
	this->boxColor = boxColor;
	this->highlightColor = highlightColor;
	this->textString = textString;
	this->position = position;
	this->size = size;
	this->key = key;
	this->isHighlight = false;

	buttonRect.setFillColor(boxColor);
	buttonRect.setSize(size);
	buttonRect.setPosition(position);
	buttonRect.setOutlineThickness(5);
	buttonRect.setOutlineColor(textColor);
}

Button::~Button()
{
}

void Button::setHighlight(bool isHighlight)
{
	this->isHighlight = isHighlight;
}

bool Button::isHighlighted()
{
	return this->isHighlight;
}

bool Button::keyEvent(sf::Keyboard::Key key)
{
	if (this->key == key)
	{
		return true;
	}
	return false;
}

void Button::render(sf::RenderWindow& window, sf::Text& text)
{
	buttonRect.setOutlineColor(isHighlight ? highlightColor : textColor);
	window.draw(buttonRect);

	text.setFillColor(isHighlight ? highlightColor : textColor);
	text.setCharacterSize(fontSize);
	text.setString(textString);
	text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
	text.setPosition(buttonRect.getPosition() + (buttonRect.getSize() / 2.f));
	window.draw(text);

	// reset text origin
	text.setOrigin(0, 0);
}

bool Button::mouseInButton(sf::RenderWindow& window)
{
	return mouseInBox(window, position.x, position.y, size.x, size.y);
}

bool Button::posInButton(int x, int y)
{
	return posInBox(x, y, position.x, position.y, size.x, size.y);
}
