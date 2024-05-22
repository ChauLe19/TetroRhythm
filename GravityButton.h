#pragma once
#include "Button.h"

class GravityButton : public Button
{
private:
	int progress = 0;
	sf::RectangleShape progressRect;
public:
	GravityButton(sf::Color textColor, int fontSize, sf::Color boxColor, std::string textString, sf::Vector2f position, sf::Vector2f size, sf::Color highlightColor = sf::Color::White, sf::Keyboard::Key key = sf::Keyboard::Unknown);
	~GravityButton();
	void setProgress(int progress);
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
};

