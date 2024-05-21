#include "GravityButton.h"

GravityButton::GravityButton(sf::Color textColor, int fontSize, sf::Color boxColor, std::string textString, sf::Vector2f position, sf::Vector2f size, sf::Color highlightColor, sf::Keyboard::Key key)
	:Button(textColor, fontSize, boxColor, textString, position, size, highlightColor, key)
{
	progressRect.setFillColor(sf::Color(0, 186, 211, 200));
	progressRect.setPosition(position);
	progressRect.setOutlineThickness(5);
	progressRect.setOutlineColor(sf::Color::Transparent);
}

GravityButton::~GravityButton()
{
}

void GravityButton::setProgress(int progress)
{
	this->progress = std::clamp(progress, 0, 100);
}

void GravityButton::render(sf::RenderWindow& window, sf::Text& text)
{
	Button::render(window, text);
	int sizeY = size.y * progress / 100;
	progressRect.setSize(sf::Vector2f(size.x, sizeY));
	progressRect.setPosition(sf::Vector2f(position.x, position.y + size.y - sizeY));
	window.draw(progressRect);

	text.setFillColor(isHighlight ? highlightColor : textColor);
	text.setCharacterSize(fontSize);
	text.setString(textString);
	text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
	text.setPosition(buttonRect.getPosition() + (buttonRect.getSize() / 2.f));
	window.draw(text);

	// reset text origin
	text.setOrigin(0, 0);
}
