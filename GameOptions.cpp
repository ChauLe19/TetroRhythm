#include "GameOptions.h"

int GameOptions::clamp(int var, int min, int max)
{
	if (var < min)
	{
		return min;
	}
	else if (var > max)
	{
		return max;
	}
	return var;
}

GameOptions::GameOptions(GameBase*& gamePtr, Controls_Settings& settings)
	: gamePtr(gamePtr), settings(settings)
{
	cursorX = 0;
	cursorY = 0;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
}

GameOptions::~GameOptions()
{
}

void GameOptions::tick(RenderWindow& window)
{
}

void GameOptions::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setPosition(100, 100);
	text.setCharacterSize(30);
	text.setString("Game Options");
	window.draw(text);

	drawGameModeOption(window, "Auto Drop Beat", 50, 200, cursorY == 0);	// get as many points as you can but a beat will force a hard drop
	drawGameModeOption(window, "Drop on Beat", 50, 300, cursorY == 1);		// drop blocks on the beat receives bonus

}

void GameOptions::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Escape:
		state = State::MENU;
		break;
	case Keyboard::Key::Enter:
		state = State::GAME;
		delete gamePtr;
		switch (cursorY)
		{
		case 0:
			gamePtr = new AutoDropGame(settings);
			break;
		case 1:
			gamePtr = new DropToTheBeatGame(settings);
			break;
		}
		gamePtr->start();
		break;
	case Keyboard::Key::Up:
		cursorY = clamp(cursorY - 1, 0, 1);
		break;
	case Keyboard::Key::Down:
		cursorY = clamp(cursorY + 1, 0, 1);
		break;
	}
}

void GameOptions::drawGameModeOption(RenderWindow& window, string gameMode, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(300, 50));
		rect.setPosition(x, y - 25);
		rect.setFillColor(Color::White);
		window.draw(rect);

		text.setFillColor(Color::Black);

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y);
	text.setCharacterSize(20);
	text.setString(gameMode);
	window.draw(text);

}
