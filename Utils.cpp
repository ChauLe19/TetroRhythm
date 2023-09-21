#include "Utils.h"
#include <sstream>

bool mouseInBox(RenderWindow& window, int x, int y, int width, int height)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	return (mouseViewPos.x >= x && mouseViewPos.x <= x + width
		&& mouseViewPos.y >= y && mouseViewPos.y <= y + height);
}

bool posInBox(int posX, int posY, int x, int y, int width, int height)
{
	return (posX >= x && posX <= x + width
		&& posY >= y && posY <= y + height);
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
	rect.setFillColor(boxColor);
	rect.setSize(Vector2f(width, height));
	rect.setPosition(Vector2f(x, y));
	rect.setOutlineThickness(5);
	rect.setOutlineColor(Color::White);
	window.draw(rect);

	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setString(textString);
	text.setPosition(x + width / 2 - text.getLocalBounds().width / 2, y + height /2 - text.getLocalBounds().height);
	window.draw(text);
}

// if isPaddingRight == true, paddedChar will fill the right side, else fill the left side
std::string getPaddingString(std::string const& str, int n, char paddedChar, bool isPaddingRight)
{
	std::ostringstream ss;
	if (isPaddingRight)
	{
		ss << std::left << std::setfill(paddedChar) << std::setw(n) << str;
	}
	else
	{
		ss << std::right << std::setfill(paddedChar) << std::setw(n) << str;
	}
	return ss.str();
}

std::string getRank(int score, int threshold)
{
	if (score == 0)
	{
		return "F";
	}
	else if (score >= threshold) // 100%
	{
		return "SS";
	}
	else if (score >= threshold * 95 / 100)
	{
		return "S";
	}
	else if (score >= threshold * 90 / 100)
	{
		return "A";
	}
	else if (score >= threshold * 85 / 100)
	{
		return "B";
	}
	else if (score >= threshold * 75 / 100)
	{
		return "C";
	}
	else if (score >= threshold * 60 / 100)
	{
		return "D";
	}
	else
	{
		return "F";
	}
}

std::string getTimeFormat(int timeInMiliseconds)
{
	return to_string(timeInMiliseconds / 1000 / 60) + ":" + to_string(timeInMiliseconds / 1000 % 60) + "." + to_string((timeInMiliseconds % 1000) / 10);
}

