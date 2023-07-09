#include "GameOptions.h"

GameOptions::GameOptions(GameBase*& gamePtr, Controls_Settings& settings)
	: gamePtr(gamePtr), settings(settings)
{
	cursorMap = 0;
	cursorMode = 0;
	font.loadFromFile("Dense-Regular.otf");
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

void GameOptions::tick(State& state, RenderWindow& window)
{
}

void GameOptions::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setCharacterSize(120);
	text.setString("Game Options");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 50);
	window.draw(text);

	drawGameModeOption(window, "Auto Drop Beat", 50, 300, cursorMode == 0);	// get as many points as you can but a beat will force a hard drop
	drawGameModeOption(window, "Drop on Beat", 50, 500, cursorMode == 1);		// drop blocks on the beat receives bonus
	drawGameModeOption(window, "Limited Time", 50, 700, cursorMode == 2);		// get the highest score in 2 min
	drawGameModeOption(window, "Endless", 50, 900, cursorMode == 3);		// just play

	CircleShape triangle(60, 3);
	triangle.setScale(0.5, 0.5);
	triangle.setPosition(1024, 512);
	triangle.rotate(90);
	triangle.setFillColor(choosingMap ? Color::White : Color(128, 128, 128, 255));
	window.draw(triangle);


	int tempCursor = cursorMap - 1;
	int size = maps.size();
	for (int i = 0; i < 3 && tempCursor < size; ++tempCursor, ++i)
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
			gamePtr = new LimitedTimeGame(settings, fs::absolute(maps[cursorMap]).string());
			break;
		case 3:
			gamePtr = new EndlessGame(settings, fs::absolute(maps[cursorMap]).string());
			break;
		}
		gamePtr->start();
		break;
	case Keyboard::Key::Up:
		if (choosingMap)
		{
			cursorMap = clamp(cursorMap - 1, 0, (int)maps.size() - 1);
		}
		else
		{
			cursorMode = clamp(cursorMode - 1, 0, modeCount - 1);
		}
		break;
	case Keyboard::Key::Down:
		if (choosingMap)
		{
			cursorMap = clamp(cursorMap + 1, 0, (int)maps.size() - 1);
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

void GameOptions::mouseEvent(State& state, RenderWindow& window, Event event)
{
}

void GameOptions::drawGameModeOption(RenderWindow& window, string gameMode, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(500, 100));
		rect.setPosition(x, y - 15);
		rect.setFillColor(Color(125, 125, 125, 255));
		window.draw(rect);
		rect.setPosition(x, y - 25);
		rect.setFillColor(Color::White);
		window.draw(rect);

		text.setFillColor(Color(0, 0, 50, 255));

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y);
	text.setCharacterSize(60);
	text.setString(gameMode);
	window.draw(text);

}
