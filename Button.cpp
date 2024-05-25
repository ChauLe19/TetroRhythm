#include "Button.h"
#include "AssetManager.h"

Button::Button(sf::Text text) : Button(sf::RectangleShape(), text, sf::Color::White, sf::Color::Blue)
{
	setFillColor(sf::Color::Transparent);
};

Button::Button(sf::RectangleShape buttonRect, sf::Text text, sf::Color baseColor, sf::Color highlightColor)
{
	this->buttonRect = buttonRect;
	this->text = text;

	this->baseColor = baseColor;
	this->highlightColor = highlightColor;
	this->isHighlight = false;

	this->buttonRect.setOutlineThickness(5);
	this->buttonRect.setOutlineColor(baseColor);
	this->text.setFillColor(baseColor);

	recomputePosition();
}

Button::Button(sf::Color baseColor, int fontSize, sf::Color boxColor, std::string textString, sf::Vector2f position, sf::Vector2f size, sf::Color highlightColor, sf::Keyboard::Key key)
{
	this->baseColor = baseColor;
	this->boxColor = boxColor;
	this->highlightColor = highlightColor;
	this->key = key;
	this->isHighlight = false;

	buttonRect.setPosition(position);
	buttonRect.setSize(size);
	buttonRect.setFillColor(boxColor);
	buttonRect.setSize(size);
	buttonRect.setOutlineThickness(5);
	buttonRect.setOutlineColor(baseColor);

	text.setCharacterSize(fontSize);
	text.setString(textString);
	text.setFillColor(baseColor);
	text.setFont(AssetManager::getInstance()->getFont("game font"));

	recomputePosition();
}

Button::~Button()
{
}

sf::Vector2f Button::getPosition()
{
	return this->buttonRect.getPosition();
}

void Button::setSize(const sf::Vector2f& size)
{
	this->buttonRect.setSize(size);
	recomputePosition();
}

sf::Vector2f Button::getSize()
{
	return this->buttonRect.getSize();
}

void Button::setFont(const sf::Font& font)
{
	this->text.setFont(font);
	recomputePosition();
}

void Button::setFontSize(unsigned int fontSize)
{
	this->text.setCharacterSize(fontSize);
	recomputePosition();
}

void Button::setTextString(std::string textString)
{
	this->text.setString(textString);
	recomputePosition();
}

void Button::recomputePosition()
{
	text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
	text.setPosition(buttonRect.getPosition() + (buttonRect.getSize() / 2.f));
}

void Button::setHighlightColor(const sf::Color& color)
{
	highlightColor = color;
}

void Button::setBaseColor(const sf::Color& color)
{
	this->baseColor = color;
}

void Button::setColor(const sf::Color& baseColor, const sf::Color& highlightColor)
{
	setBaseColor(baseColor);
	setHighlightColor(highlightColor);
}

void Button::setHighlight(bool isHighlight)
{
	this->isHighlight = isHighlight;
	buttonRect.setOutlineColor(isHighlight ? highlightColor : baseColor);
	text.setFillColor(isHighlight ? highlightColor : baseColor);
}

void Button::setPosition(const sf::Vector2f& pos)
{
	buttonRect.setPosition(pos);
	recomputePosition();
}

void Button::setFillColor(const sf::Color& color)
{
	buttonRect.setFillColor(color);
}

void Button::setShortcut(const sf::Keyboard::Key& key)
{
	this->key = key;
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

bool Button::mouseInButton(sf::RenderWindow& window)
{
	return mouseInBox(window, getPosition().x, getPosition().y, getSize().x, getSize().y);
}

bool Button::posInButton(int x, int y)
{
	return posInBox(x, y, getPosition().x, getPosition().y, getSize().x, getSize().y);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(buttonRect, states);
	target.draw(text, states);
}
