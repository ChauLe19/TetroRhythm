#pragma once
#include "Button.h"

class GravityButton : public Button
{
private:
	int progress = 0;
	RectangleShape progressRect;
public:
	GravityButton(Color textColor, int fontSize, sf::Color boxColor, string textString, Vector2f position, Vector2f size, sf::Color highlightColor = Color::White, Keyboard::Key key = Keyboard::Unknown);
	~GravityButton();
	void setProgress(int progress);
	void render(RenderWindow& window, Text& text);
};

