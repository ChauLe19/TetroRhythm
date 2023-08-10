#include "GameOptions.h"
#include "Menu.h"

GameOptions::GameOptions(StateManager& stateManager)
	: StateScreen(stateManager)
{
	cursorMap = 0;
	cursorMode = 0;
	text.setFont(assetManager->getFont("game font"));
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
	text.setCharacterSize(120);
	text.setString("Game Options");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 50);
	window.draw(text);

	drawGameModeOption(window, "Drop on Beat", 50, 300, cursorMode == 0);		// drop blocks on the beat receives bonus
	drawGameModeOption(window, "Limited Time", 50, 500, cursorMode == 1);		// get the highest score in 2 min
	drawGameModeOption(window, "Endless", 50, 700, cursorMode == 2);		// just play

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

void GameOptions::keyEvent(Event event)
{
	if (event.type != Event::KeyPressed) return;
	switch (event.key.code)
	{
	case Keyboard::Key::Escape:
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		break;
	case Keyboard::Key::Return:
		if (!choosingMap) // if player is not choosing map (choosing mode), enter allow user to choose map
		{
			choosingMap = true;
			return;
		}
		GameBase* gamePtr;
		switch (cursorMode)
		{
		case 0:
			gamePtr = new DropToTheBeatGame(stateManager, fs::absolute(maps[cursorMap]).string());
			break;
		case 1:
			gamePtr = new LimitedTimeGame(stateManager, fs::absolute(maps[cursorMap]).string());
			break;
		case 2:
			gamePtr = new EndlessGame(stateManager, fs::absolute(maps[cursorMap]).string());
			break;
		default:
			gamePtr = new DropToTheBeatGame(stateManager, fs::absolute(maps[cursorMap]).string());
			break;
		}
		stateManager.addState(std::unique_ptr<StateScreen>(gamePtr));
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

void GameOptions::mouseEvent(RenderWindow& window, Event event)
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
