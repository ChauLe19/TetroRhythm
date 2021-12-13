#include "Button.h"

Button::Button(Color textColor, int fontSize, Color boxColor, string textString, int x, int y, int width, int height, Keyboard::Key key)
{
	this->textColor = textColor;
	this->fontSize = fontSize;
	this->boxColor = boxColor;
	this->textString = textString;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->key = key;
}

Button::~Button()
{
}

// Not sure how to use function pointer
//void Button::doFunc()
//{
//	f();
//}

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
	createButton(window, text, textColor, fontSize, boxColor, textString, width, height, x, y);
}

bool Button::mouseInButton(RenderWindow& window)
{
	return mouseInBox(window, x, y, width, height);
}
