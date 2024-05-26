#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <stack>

class Button;
class ButtonGroup
{
public:
	ButtonGroup();

	void addButton(Button* button);
	void removeButton(Button* button);

	void setSelectedButton(Button* selectedButton);

	void mouseEvent(sf::RenderWindow& window, sf::Event event);

private:
	void deselectAllButtons();

	bool isExclusive = true;
	std::stack<Button*> selectedButtons;
	std::set<Button*> buttons;

	friend class Button;
};

