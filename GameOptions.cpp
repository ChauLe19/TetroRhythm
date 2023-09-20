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

void GameOptions::tick(const float & dt, RenderWindow& window)
{
}

void GameOptions::render(RenderWindow& window)
{
	RenderTexture mapsTexture;
	mapsTexture.create(1000, 500);

	mapsTexture.clear(Color::Transparent);
	mapsTexture.display();

	text.setFillColor(Color::White);
	text.setCharacterSize(120);
	text.setString("Game Options");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 50);
	window.draw(text);

	dropOnBeatGameButton.setHighlight(false);
	limitedGameButton.setHighlight(false);
	endlessGameButton.setHighlight(false);
	switch (cursorMode)
	{
	case 0:
		dropOnBeatGameButton.setHighlight(true);
		break;
	case 1:
		limitedGameButton.setHighlight(true);
		break;
	case 2:
		endlessGameButton.setHighlight(true);
		break;
	}

	dropOnBeatGameButton.render(window, text);		// drop blocks on the beat receives bonus

	limitedGameButton.render(window, text);		// get the highest score in 2 min
	text.setFillColor(limitedGameButton.isHighlighted() ? Color(0, 186, 211) : Color::White);
	text.setCharacterSize(30);
	text.setString("Highscore: " + to_string(GameSettings::getInstance()->getHighscores()->limit));
	text.setPosition(200, 500 - 40);
	window.draw(text);

	endlessGameButton.render(window, text);	// just play
	text.setFillColor(endlessGameButton.isHighlighted() ? Color(0, 186, 211) : Color::White);
	text.setCharacterSize(30);
	text.setString("Highscore: " + to_string(GameSettings::getInstance()->getHighscores()->endless));
	text.setPosition(200, 700 - 40);
	window.draw(text);


	int size = maps.size();
	for (int i = 0; i < size; ++i)
	{
		drawGameModeOption(mapsTexture, maps[i].filename().string(), 0, i * 200 + mapRenderOffset + 200, cursorMap == i);
	}

	Sprite sprite(mapsTexture.getTexture());
	sprite.setPosition(2048 - 1000, 300);
	window.draw(sprite);

	startButton.render(window, text);
	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(assetManager->getDrawable("back button hl"));
	}
	else
	{
		window.draw(assetManager->getDrawable("back button"));
	}
}

void GameOptions::keyEvent(const float & dt, Event event)
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
			mapRenderOffset = -cursorMap * 200;
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
			mapRenderOffset = -cursorMap * 200;
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

void GameOptions::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	static bool isPressed = false;
	static Vector2f pressedPosition = Vector2f(0,0);
	static int prevMapRenderOffset = 0;
	if (event.type == Event::MouseMoved)
	{
		startButton.setHighlight(startButton.mouseInButton(window));
	}
	else if (event.type == Event::MouseButtonPressed && startButton.mouseInButton(window))
	{
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
	}
	else if (event.type == Event::MouseButtonPressed && dropOnBeatGameButton.mouseInButton(window))
	{
		cursorMode = 0;
	}
	else if (event.type == Event::MouseButtonPressed && limitedGameButton.mouseInButton(window))
	{
		cursorMode = 1;
	}
	else if (event.type == Event::MouseButtonPressed && endlessGameButton.mouseInButton(window))
	{
		cursorMode = 2;
	}
	else if (event.type == Event::MouseButtonPressed && mouseInBox(window, 2048 - 1000, 300, 1000, 700))
	{
		isPressed = true;
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
		pressedPosition = Vector2f(mouseViewPos.x, mouseViewPos.y);
		prevMapRenderOffset = mapRenderOffset;
	}
	else if (event.type == Event::MouseButtonPressed && mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
	}
	else if (isPressed && Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
		mapRenderOffset = prevMapRenderOffset;
		mapRenderOffset += mouseViewPos.y - pressedPosition.y;
		cursorMap = clamp( - (mapRenderOffset - 100) / 200, 0, (int)maps.size() - 1);
	}
	else if (event.type == Event::MouseButtonReleased)
	{
		isPressed = false;
		mapRenderOffset = -cursorMap * 200;
		prevMapRenderOffset = mapRenderOffset;
	}
}

void GameOptions::drawGameModeOption(RenderTexture& window, string gameMode, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(window.getSize().x, 150));
		rect.setPosition(x, y - 38);
		rect.setFillColor(Color(0, 186, 211));
		window.draw(rect);

		text.setFillColor(Color::Black);

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y);
	text.setCharacterSize(60);
	text.setString(gameMode);
	window.draw(text);

	text.setFillColor(isHighlight ? Color(50, 50, 50) : Color(200, 200, 200));
	text.setPosition(x, y - 30);
	text.setCharacterSize(30);
	std::map<std::string, int> thresholds = GameSettings::getInstance()->getHighscores()->dropToBeatThreshold;
	auto highscores = GameSettings::getInstance()->getHighscores()->dropToBeatHS;
	int highscore = highscores.find(gameMode) != highscores.end() ? highscores.at(gameMode) : 0;
	int threshold = thresholds.find(gameMode) != thresholds.end() ? thresholds.at(gameMode) : 1;

	text.setString("Rank: " + getRank(highscore, threshold) + "\t HS : " + to_string(highscore));
	window.draw(text);

}
