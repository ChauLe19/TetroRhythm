#include "GravityButton.h"

GravityButton::GravityButton(Color textColor, int fontSize, sf::Color boxColor, string textString, Vector2f position, Vector2f size, sf::Color highlightColor, Keyboard::Key key)
	:Button(textColor, fontSize, boxColor, textString, position, size, highlightColor, key)
{
	progressRect.setFillColor(Color(0, 186, 211, 200));
	progressRect.setPosition(position);
	progressRect.setOutlineThickness(5);
	progressRect.setOutlineColor(Color::Transparent);
}

GravityButton::~GravityButton()
{
}

void GravityButton::setProgress(int progress)
{
	this->progress = clamp(progress, 0, 100);
}

void GravityButton::render(RenderWindow& window, Text& text)
{
	int sizeY = size.y * progress / 100;
	progressRect.setSize(Vector2f(size.x, sizeY));
	progressRect.setPosition(Vector2f(position.x, position.y + size.y - sizeY));
	window.draw(progressRect);

	Button::render(window, text);
}
