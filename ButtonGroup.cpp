#include "ButtonGroup.h"
#include "Button.h"

ButtonGroup::ButtonGroup() : 
	buttons()
{
}

void ButtonGroup::addButton(Button* button)
{
	buttons.insert(button);
	button->setButtonGroup(this);
}

void ButtonGroup::removeButton(Button* button)
{
	buttons.erase(button);
	if (button->getButtonGroup() == this)
	{
		button->setButtonGroup(nullptr);
	}
}

void ButtonGroup::setSelectedButton(Button* selectedButton)
{
	if (isExclusive)
	{
		for (Button* button : buttons)
		{
			if (button != selectedButton) button->setSelected(false);
		}
	}
	selectedButton->setSelected(true);
}

void ButtonGroup::deselectAllButtons()
{
	
}

void ButtonGroup::mouseEvent(sf::RenderWindow& window, sf::Event event)
{
	for (Button* button : buttons)
	{
		button->mouseEvent(window, event);
	}
}


