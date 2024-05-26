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
	this->m_isSelectable = false;

	this->buttonRect.setOutlineThickness(5);
	this->buttonRect.setOutlineColor(baseColor);
	this->text.setFillColor(baseColor);

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

void Button::setCallback(std::function<void(void)> callback)
{
	this->callback = callback;
}

bool Button::isSelectable()
{
	return this->m_isSelectable;
}

void Button::setSelectable(bool selectable)
{
	this->m_isSelectable = selectable;
}

void Button::setSelected(bool selected)
{
	if (selected)
	{
		this->state = Selected;
	}
	else
	{
		this->state = Idle;
	}
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

void Button::mouseEvent(sf::RenderWindow& window, sf::Event event)
{
	switch (state)
	{
	case Idle:
		if (mouseInButton(window))
		{
			state = Hover;
			buttonRect.setOutlineColor(highlightColor);
			text.setFillColor(highlightColor);
		}
		break;
	case Hover:
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mouseInButton(window))
		{
			state = Pressed;
			buttonRect.setOutlineColor(highlightColor);
			text.setFillColor(highlightColor);
		}
		else if (!mouseInButton(window))
		{
			state = Idle;
			buttonRect.setOutlineColor(baseColor);
			text.setFillColor(baseColor);
		}
		break;
	case Pressed:
		buttonRect.setOutlineColor(highlightColor);
		text.setFillColor(highlightColor);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && mouseInButton(window))
		{
			if (isSelectable())
			{
				state = Selected;
			}
			else
			{
				state = Idle;
			}
			callback();
		}
		else if (!mouseInButton(window))
		{
			state = PressedOutside;
		}
		break;
	case PressedOutside:
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !mouseInButton(window))
		{
			state = Idle;
			buttonRect.setOutlineColor(baseColor);
			text.setFillColor(baseColor);
		}
		else if (mouseInButton(window))
		{
			state = Pressed;
		}
		break;
	case Selected:
		if (mouseInButton(window))
		{
			state = SelectedHover;
			buttonRect.setOutlineColor(highlightColor);
			text.setFillColor(highlightColor);
		}
		break;
	case SelectedHover:
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mouseInButton(window))
		{
			state = SelectedPressed;
		}
		else if (!mouseInButton(window))
		{
			state = SelectedPressedOutside;
		}
		break;
	case SelectedPressed:
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && mouseInButton(window))
		{
			state = Idle;
			callback();
			buttonRect.setOutlineColor(baseColor);
			text.setFillColor(baseColor);
		}
		else if (!mouseInButton(window))
		{
			state = PressedOutside;
		}
		break;
	case SelectedPressedOutside:
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !mouseInButton(window))
		{
			state = Selected;
		}
		else if (mouseInButton(window))
		{
			state = SelectedPressed;
		}
		break;
	default:
		break;
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(buttonRect, states);
	target.draw(text, states);
}
