#include "Utils.h"

bool mouseInBox(RenderWindow& window, int x, int y, int width, int height)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	return (mouseViewPos.x >= x && mouseViewPos.x <= x + width
		&& mouseViewPos.y >= y && mouseViewPos.y <= y + height);
}

bool mouseInCircle(RenderWindow& window, int x, int y, int r)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	return (mouseViewPos.x - x) * (mouseViewPos.x - x) + (mouseViewPos.y - y) * (mouseViewPos.y - y) <= r * r;
}

void createButton(RenderWindow& window, Text& text,  Color textColor, int textSize, Color boxColor, string textString, int width, int height, int x, int y)
{
	RectangleShape rect;
	rect.setSize(Vector2f(width, height));
	rect.setFillColor(Color(boxColor.r - 100, boxColor.g - 100, boxColor.b - 100, 255));
	rect.setPosition(Vector2f(x, y + 10));
	window.draw(rect);

	rect.setFillColor(boxColor);
	rect.setSize(Vector2f(width, height));
	rect.setPosition(Vector2f(x, y));
	window.draw(rect);

	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setString(textString);
	text.setPosition(x + width / 2 - text.getLocalBounds().width / 2, y - 10);
	window.draw(text);
}

