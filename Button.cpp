#include "Button.h"

Button::Button(Color textColor, int fontSize, Color boxColor, string textString, Vector2f position, Vector2f size, Color highlightColor, Keyboard::Key key)
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

bool Button::keyEvent(Keyboard::Key key)
{
	if (this->key == key)
	{
		return true;
	}
	return false;
}

void Button::render(RenderWindow& window, Text& text)
{
	buttonRect.setOutlineColor(isHighlight ? highlightColor : textColor);
	window.draw(buttonRect);

	text.setFillColor(isHighlight ? highlightColor : textColor);
	text.setCharacterSize(fontSize);
	text.setString(textString);
	text.setPosition(position.x + size.x / 2 - text.getLocalBounds().width / 2, position.y + size.y /2 - text.getLocalBounds().height);
	window.draw(text);
}

bool Button::mouseInButton(RenderWindow& window)
{
	return mouseInBox(window, position.x, position.y, size.x, size.y);
}

bool Button::posInButton(int x, int y)
{
	return posInBox(x, y, position.x, position.y, size.x, size.y);
}
