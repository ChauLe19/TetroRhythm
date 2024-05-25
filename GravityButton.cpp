#include "GravityButton.h"

GravityButton::GravityButton(const sf::Text& text) : Button(text)
{
	progressRect.setFillColor(sf::Color(0, 186, 211, 200));
	progressRect.setOutlineThickness(5);
	progressRect.setOutlineColor(sf::Color::Transparent);
}

GravityButton::~GravityButton()
{
}

void GravityButton::setPosition(const sf::Vector2f& position)
{
	Button::setPosition(position);
	int sizeY = getSize().y * progress / 100;
	progressRect.setPosition(sf::Vector2f(getPosition().x, getPosition().y + getSize().y - sizeY));
}

void GravityButton::setProgressFillColor(const sf::Color& color)
{
	progressRect.setFillColor(color);
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
