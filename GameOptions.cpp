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
	cursorMap = 0;
	cursorMode = 0;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);

	std::string path = "BeatMaps";
	for (const auto& entry : fs::directory_iterator(path))
	{
		maps.push_back(entry.path());
	}
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
	text.setPosition(600, 50);
	text.setCharacterSize(100);
	text.setString("Game Options");
	window.draw(text);

	drawGameModeOption(window, "Auto Drop Beat", 50, 300, cursorMode == 0);	// get as many points as you can but a beat will force a hard drop
	drawGameModeOption(window, "Drop on Beat", 50, 500, cursorMode == 1);		// drop blocks on the beat receives bonus
	drawGameModeOption(window, "Endless", 50, 700, cursorMode == 2);		// drop blocks on the beat receives bonus

	CircleShape triangle(60, 3);
	triangle.setScale(0.5, 0.5);
	triangle.setPosition(1024, 512);
	triangle.rotate(90);
	triangle.setFillColor(choosingMap ? Color::White : Color(128, 128, 128, 255));
	window.draw(triangle);


	int tempCursor = cursorMap - 1;
	int size = maps.size();
	for (int i = 0;
		i < 3 && tempCursor < size;
		++tempCursor, ++i)
	{
		if (tempCursor >= 0)
		{
			drawGameModeOption(window, maps[tempCursor].filename().string(), 1100, 300 + i * 200, cursorMap == tempCursor);
		}
	}

}

void GameOptions::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Escape:
		state = State::MENU;
		break;
	case Keyboard::Key::Enter:
		if (!choosingMap) // if player is not choosing map (choosing mode), enter allow user to choose map
		{
			choosingMap = true;
			return;
		}
		state = State::GAME;
		delete gamePtr;
		switch (cursorMode)
		{
		case 0:
			gamePtr = new AutoDropGame(settings, fs::absolute(maps[cursorMap]).string());
			break;
		case 1:
			gamePtr = new DropToTheBeatGame(settings, fs::absolute(maps[cursorMap]).string());
			break;
		case 2:
			gamePtr = new EndlessGame(settings, fs::absolute(maps[cursorMap]).string());
			break;
		}
		gamePtr->start();
		break;
	case Keyboard::Key::Up:
		if (choosingMap)
		{
			cursorMap = clamp(cursorMap - 1, 0, maps.size() - 1);
		}
		else
		{
			cursorMode = clamp(cursorMode - 1, 0, modeCount - 1);
		}
		break;
	case Keyboard::Key::Down:
		if (choosingMap)
		{
			cursorMap = clamp(cursorMap + 1, 0, maps.size() - 1);
		}
		else
		{
			cursorMode = clamp(cursorMode + 1, 0, modeCount - 1);
		}
		break;
	case Keyboard::Key::Right:
		if (!choosingMap)
		{
			choosingMap = true;
		}
		break;
	case Keyboard::Key::Left:
		if (choosingMap)
		{
			choosingMap = false;
		}
	}
}

void GameOptions::mouseEvent(RenderWindow& window)
{
}

void GameOptions::drawGameModeOption(RenderWindow& window, string gameMode, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(500, 100));
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
	text.setCharacterSize(50);
	text.setString(gameMode);
	window.draw(text);

}
