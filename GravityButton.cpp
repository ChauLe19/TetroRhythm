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
	int sizeY = getSize().y * progress / 100;
	progressRect.setSize(sf::Vector2f(getSize().x, sizeY));
	progressRect.setPosition(sf::Vector2f(getPosition().x, getPosition().y + getSize().y - sizeY));
}

void GravityButton::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	Button::draw(window);
	window.draw(progressRect);
	window.draw(text);
}
