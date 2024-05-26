#include "Button.h"
#include "AssetManager.h"
#include "ButtonGroup.h"

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
	this->m_isHighlighted = false;

	this->buttonRect.setOutlineThickness(5);
	this->buttonRect.setOutlineColor(baseColor);
	this->text.setFillColor(baseColor);

	recomputePosition();
}

void Button::refreshColors()
{
	this->buttonRect.setOutlineColor(isHighlighted() ? highlightColor : baseColor);
	this->text.setFillColor(isHighlighted() ? highlightColor : baseColor);
}

Button::~Button()
{
}

void Button::setButtonGroup(ButtonGroup* group)
{
	this->group = group;
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
	refreshColors();
}

void Button::setBaseColor(const sf::Color& color)
{
	this->baseColor = color;
	refreshColors();
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

ButtonGroup* Button::getButtonGroup()
{
	return this->group;
}

void Button::setCallback(std::function<void(void)> callback)
{
	this->callback = callback;
}

void Button::setHighlighted(bool isHighlighted)
{
	if (m_isHighlighted != isHighlighted)
	{
		m_isHighlighted = isHighlighted;
		this->buttonRect.setOutlineColor(isHighlighted ? highlightColor : baseColor);
		this->text.setFillColor(isHighlighted ? highlightColor : baseColor);
	}
}

bool Button::isHighlighted()
{
	return m_isHighlighted;
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
	if (selected && !isSelected())
	{
		this->state = Selected;
		setHighlighted(true);
		if (group) group->setSelectedButton(this);
	}
	else if (!selected && isSelected())
	{
		this->state = Idle;
		setHighlighted(false);
	}
}

bool Button::isSelected()
{
	return state == Selected || state == SelectedHover || state == SelectedPressed || state == SelectedPressedOutside;
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
		setHighlighted(false);
		if (mouseInButton(window))
		{
			state = Hover;
		}
		break;
	case Hover:
		setHighlighted(true);
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mouseInButton(window))
		{
			state = Pressed;
		}
		else if (!mouseInButton(window))
		{
			state = Idle;
		}
		break;
	case Pressed:
		setHighlighted(true);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (isSelectable())
			{
				state = Selected;
				if (group) group->setSelectedButton(this);
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
		setHighlighted(true);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			state = Idle;
		}
		else if (mouseInButton(window))
		{
			state = Pressed;
		}
		break;
	case Selected:
		setHighlighted(true);
		if (mouseInButton(window))
		{
			state = SelectedHover;
		}
		break;
	case SelectedHover:
		setHighlighted(true);
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			state = SelectedPressed;
		}
		else if (!mouseInButton(window))
		{
			state = Selected;
		}
		break;
	case SelectedPressed:
		setHighlighted(true);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (group != nullptr)
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
			state = SelectedPressedOutside;
		}
		break;
	case SelectedPressedOutside:
		setHighlighted(true);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
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
