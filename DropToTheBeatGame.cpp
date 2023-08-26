#include "DropToTheBeatGame.h"

DropToTheBeatGame::DropToTheBeatGame(StateManager &stateManager, string folderPath) : GameBase(stateManager, folderPath)
{
	loadStaticAssets();
	this->clearBoardButton = new Button(Color::Black, 100, Color::White, "Clear", boardX - 200 - boardSquareSize, boardY + boardWidth * boardSquareSize - 200, 200, 200, Keyboard::Unknown);

	// Load map info
	fs::path txtPath = folderPath;
	txtPath.append(txtPath.filename().string() + ".txt");

	if (!fs::exists(txtPath))
		cerr << "Text file doesn't exist." << endl;

	std::ifstream inFile;
	inFile.open(txtPath);
	if (!inFile)
	{
		cerr << "Unable to open file " + txtPath.string() << endl;;
	}

	char beat[10];
	inFile.getline(beat, 10, '\r');
	while (inFile.getline(beat, 10, '\r'))
	{
		beatsTime.push_back(atoi(beat));
	}
	beatIt = beatsTime.begin();
	nextBeatTimeMS = *beatIt;

	currentPiecePtr = &nextPiece();
}


DropToTheBeatGame::~DropToTheBeatGame()
{
	delete this->clearBoardButton;
}

void DropToTheBeatGame::loadStaticAssets()
{
	const int BarWindow = 2000;
	const int boardWidthPx = boardWidth * boardSquareSize;
	RectangleShape *beatBar = new RectangleShape(Vector2f(boardWidthPx, 20));
	beatBar->setPosition(boardX, boardY - 50);
	beatBar->setOutlineColor(Color(205, 92, 92, 0));
	beatBar->setOutlineThickness(5);
	beatBar->setFillColor(Color(211, 33, 44));

	// ALMOST zone = 400ms each side = 200ms
	const static int AlmostWindow = 800;
	RectangleShape *almostBar = new RectangleShape(Vector2f(boardWidthPx * AlmostWindow / BarWindow, 20));
	almostBar->setPosition(boardX + boardWidthPx/2 - (boardWidthPx * (AlmostWindow/2) / BarWindow ), boardY - 50);
	almostBar->setFillColor(Color(255, 152, 14));

	// HIT zone = 400ms each side = 200ms
	const static int HitWindow = 400;
	RectangleShape *hitBar = new RectangleShape(Vector2f(boardWidthPx * HitWindow / BarWindow, 20));
	hitBar->setPosition(boardX + boardWidthPx/2 - (boardWidthPx * (HitWindow/2) / BarWindow), boardY - 50);
	hitBar->setFillColor(Color(6, 156, 86));

	RectangleShape *healthBar = new RectangleShape();
	healthBar->setPosition(20, 40);
	healthBar->setSize(Vector2f(500, 20));
	healthBar->setFillColor(Color::Transparent);
	healthBar->setOutlineColor(Color::White);
	healthBar->setOutlineThickness(5);

	assetManager->loadDrawable("beat bar", std::unique_ptr<sf::Drawable>(beatBar));
	assetManager->loadDrawable("almost window", std::unique_ptr<sf::Drawable>(almostBar));
	assetManager->loadDrawable("hit window", std::unique_ptr<sf::Drawable>(hitBar));
	assetManager->loadDrawable("health bar", std::unique_ptr<Drawable>(healthBar));
}

void DropToTheBeatGame::tick(const float & dt, RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(dt, window);

	// every secon passed, health + 1
	/*healthCounter++;
	if (healthCounter >= 60)
	{
		health = clamp(health  + 1, 0, 100);
		healthCounter = 0;
	}*/

	// skip beat was out of 1000ms window
	if (sound.getPlayingOffset().asMilliseconds() - 1000 >= nextBeatTimeMS  && beatIt != beatsTime.end())
	{
		combo = 0;
		comboString = "TOO LATE";
		beatAccuracyCount[0]++;
		health = clamp(health - 10, 0, 100);
		prevBeatTimeMS = nextBeatTimeMS;
		beatIt++;
		nextBeatTimeMS = *beatIt;
	}

	if (health <= 0)
	{
		gameOver();
		return;
	}

	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		finished = true;
		gameOver();
		ResultScreen *resultScreenPtr = new ResultScreen(stateManager, songName, beatAccuracyCount, score, maxCombo);
		stateManager.addState(unique_ptr<StateScreen>(resultScreenPtr));
		return;
	}
}

void DropToTheBeatGame::keyEvent(const float & dt, Event event)
{
	if (event.type != Event::KeyPressed) return;
	GameBase::keyEvent(dt, event);

	// reset on top of the gamebase's reset
	if (event.key.code == Keyboard::Key::R)
	{
		restart();
	}
}

void DropToTheBeatGame::checkDropOnBeat()
{
}
void DropToTheBeatGame::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	if (finished) return;
	if (!isGameOver && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && 
		this->clearBoardButton->mouseInButton(window))
	{
		board.clearBoard();
		return;
	}
	else if (!isGameOver && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		int tempTime = sound.getPlayingOffset().asMilliseconds();

		// if pressed in 400ms window, doesn't get "TOO LATE"
		// TOO LATE	-> health -= 10
		// MISS		-> health -= 1
		// ALMOST	-> health += 1
		// HIT		-> health += 2
		if (abs(tempTime - nextBeatTimeMS) <= 200) // HIT
		{
			combo++;
			hitType = 2;
		}
		else if (abs(tempTime - nextBeatTimeMS) <= 400) // ALMOST
		{
			combo++;
			hitType = 1;

		}
		else // MISS
		{
			hitType = 0;
			combo = 0;
		}

		beatAccuracyCount[hitType]++;

		if (combo > maxCombo)
		{
			maxCombo = combo;
		}
		beatPressed = false;


		switch (hitType)
		{
			case 0:
				comboString = "MISS";
				health = clamp(health - 10, 0, 100);
			break;
			case 1:
				comboString = "ALMOST";
				health = clamp(health + 1, 0, 100);
			break;
			case 2:
				comboString = "HIT";
				health = clamp(health + 2, 0, 100);
			break;
			default:
				break;
		}

		if (*beatIt <= tempTime + 800 && beatIt != beatsTime.end())
		{
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;
			if (beatIt != beatsTime.end())
				nextBeatTimeMS = *beatIt;
		}
	}
	GameBase::mouseEvent(dt, window, event);
}

void DropToTheBeatGame::renderBeatSignal(RenderWindow& window)
{
	static vector<Color> rainbow = { Color::Red, Color(255, 165, 0), Color::Yellow, Color::Green, Color::Blue, Color(75,0,130) ,Color(127,0,255) };
	int tempRainbowIndex = rainbowIndex;

	const int innerRadius = 150;

	int maxOffsetMS = 1000; // 1000ms
	int nowTime = sound.getPlayingOffset().asMilliseconds();

	// half bar should represent 1000ms of beat
	// bar window = 2000ms
	const static int BarWindow = 2000;
	int boardWidthPx = boardWidth * boardSquareSize;


	window.draw(assetManager->getDrawable("beat bar"));
	window.draw(assetManager->getDrawable("almost window"));
	window.draw(assetManager->getDrawable("hit window"));

	for (list<int>::iterator tempBeatIt = beatIt; tempBeatIt != beatsTime.end(); ++tempBeatIt, ++tempRainbowIndex)
	{
		int bufferTime = *tempBeatIt;
		int timeOffset = bufferTime - nowTime;

		if (timeOffset > maxOffsetMS) break;
		int distanceFromEnd = timeOffset * boardWidthPx/BarWindow;
		RectangleShape preview(Vector2f(20, 50));
		preview.setOutlineThickness(2);
		preview.setOutlineColor(Color::White);
		preview.setFillColor(currentPiecePtr->getBaseColor());
		preview.setPosition(boardX + boardWidthPx / 2 - distanceFromEnd - 20 / 2, boardY - 65);
		window.draw(preview);
	}

}

void DropToTheBeatGame::restart()
{
	GameBase::restart();
	health = 100;
	healthCounter = 0;
	combo = 0;
	maxCombo = 0;
	beatPressed = false;
	beatAccuracyCount[0] = 0;
	beatAccuracyCount[1] = 0;
	beatAccuracyCount[2] = 0;
	finished = false;
	beatIt = beatsTime.begin();
	nextBeatTimeMS = *beatIt;
	prevBeatTimeMS = 0;
}

void DropToTheBeatGame::render(RenderWindow& window)
{
	GameBase::render(window);
	renderBeatSignal(window);


	RectangleShape healthRect;
	healthRect.setPosition(20, 40);
	healthRect.setSize(Vector2f(health * 5, 20));
	healthRect.setFillColor(Color::Yellow);
	healthRect.setOutlineColor(Color::Yellow);
	healthRect.setOutlineThickness(5);
	window.draw(healthRect);

	window.draw(assetManager->getDrawable("health bar"));

	text.setCharacterSize(50);
	text.setString("Combo: " + getLeftPaddingString(to_string(combo), 4, ' ') );
	text.setPosition(boardX - text.getLocalBounds().width - 100, 600);
	window.draw(text);

	text.setFillColor(Color(255, 255, 255, 200));
	text.setString(comboString);
	text.setPosition(1024 - text.getLocalBounds().width, boardY + boardSquareSize * 5 + 75 / 2);
	if (accuracyTimer > 0)
	{
		accuracyTimer--;
		window.draw(text);
	}
	this->clearBoardButton->render(window, text);



	if (isGameOver && !finished)
	{
		GameBase::renderGameOver(window);

		text.setCharacterSize(120);
		text.setFillColor(finished ? Color::Green : Color::Red);
		text.setString(finished ? "Completed" : "Failed");
		text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 400);
		window.draw(text);

		text.setCharacterSize(80);
		text.setFillColor(Color::White);
		text.setString(to_string(score));
		text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 250);
		window.draw(text);
	}
}

