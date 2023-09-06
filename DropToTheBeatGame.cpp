#include "DropToTheBeatGame.h"

DropToTheBeatGame::DropToTheBeatGame(StateManager &stateManager, string folderPath) : GameBase(stateManager, folderPath)
{
	loadStaticAssets();
	this->gravityButton = new GravityButton(Color::White, 50, Color::Transparent, "Gravity", Vector2f(boardX - 200 - boardSquareSize, boardY + boardWidth * boardSquareSize - 200), Vector2f(200, 200), Color(0, 186, 211), Keyboard::Unknown);

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

	std::map<std::string, int> thresholds = GameSettings::getHighscores()->dropToBeatThreshold;
	threshold = thresholds.find(songName) != thresholds.end() ? thresholds.at(songName) : 1;
}


DropToTheBeatGame::~DropToTheBeatGame()
{
	delete this->gravityButton;
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
	healthBar->setPosition(boardX + boardWidth * boardSquareSize + 10, boardY - 5);
	healthBar->setSize(Vector2f(20, boardHeight * boardSquareSize + 10));
	healthBar->setFillColor(Color::Transparent);
	healthBar->setOutlineColor(Color(255, 255, 255, 200));
	healthBar->setOutlineThickness(5);

	// bars for rank tracking
	int entireBarLength = 6 * boardSquareSize;
	RectangleShape *WholeRankBar = new RectangleShape();
	WholeRankBar->setPosition(boardX, boardY + 6 * boardSquareSize + 30);
	WholeRankBar->setSize(Vector2f(entireBarLength, 20));
	WholeRankBar->setFillColor(Color::Transparent);
	WholeRankBar->setOutlineColor(Color(255, 255, 255, 200));
	WholeRankBar->setOutlineThickness(5);

	assetManager->loadDrawable("beat bar", std::unique_ptr<sf::Drawable>(beatBar));
	assetManager->loadDrawable("almost window", std::unique_ptr<sf::Drawable>(almostBar));
	assetManager->loadDrawable("hit window", std::unique_ptr<sf::Drawable>(hitBar));
	assetManager->loadDrawable("health bar", std::unique_ptr<Drawable>(healthBar));
	assetManager->loadDrawable("Whole Rank bar", std::unique_ptr<Drawable>(WholeRankBar));
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
	if (beatIt != beatsTime.end() && sound.getPlayingOffset().asMilliseconds() - 1000 >= nextBeatTimeMS)
	{
		combo = 0;
		comboString = "TOO LATE";
		beatAccuracyCount[0]++;
		health = clamp(health - 10, 0, 100);
		prevBeatTimeMS = nextBeatTimeMS;
		beatIt++;
		if(beatIt != beatsTime.end())
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

void DropToTheBeatGame::gameOver()
{
	GameBase::gameOver();
	if (highscores->dropToBeatHS.find(songName) != highscores->dropToBeatHS.end())
	{
		highscores->dropToBeatHS[songName] = max(highscores->dropToBeatHS[songName], score);
	}
	else
	{
		highscores->dropToBeatHS[songName] = score;
	}
	GameSettings::saveHighscores();
}

void DropToTheBeatGame::keyEvent(const float & dt, Event event)
{
	if (event.type != Event::KeyPressed && event.type != Event::KeyReleased) return;
	map<string, Keyboard::Key> keybinds = controlsSettings->keybinds;
	if (event.type == Event::KeyReleased && (event.key.code == keybinds["HARD_DROP"] || event.key.code == keybinds["HARD_DROP_ALT"]))
	{
		checkDropOnBeat();
	}
	GameBase::keyEvent(dt, event);

	// reset on top of the gamebase's reset
	if (event.key.code == Keyboard::Key::R)
	{
		restart();
	}
}

void DropToTheBeatGame::checkDropOnBeat()
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
		score += combo;
		gravityCharge = clamp(gravityCharge + 5, 0, 100);
		gravityButton->setProgress(gravityCharge);
	}
	else if (abs(tempTime - nextBeatTimeMS) <= 400) // ALMOST
	{
		combo++;
		hitType = 1;
		score += combo;
		gravityCharge = clamp(gravityCharge + 5, 0, 100);
		gravityButton->setProgress(gravityCharge);
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
			score += 5;
		break;
		case 2:
			comboString = "HIT";
			health = clamp(health + 2, 0, 100);
			score += 10;
		break;
		default:
			break;
	}

	if (beatIt != beatsTime.end() && *beatIt <= tempTime + 800 )
	{
		prevBeatTimeMS = nextBeatTimeMS;
		beatIt++;
		if (beatIt != beatsTime.end())
			nextBeatTimeMS = *beatIt;
	}
}
void DropToTheBeatGame::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	if (finished) return;
	if (!isGameOver && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
		this->gravityButton->mouseInButton(window))
	{
		return;
	}
	if (!isGameOver && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && 
		this->gravityButton->mouseInButton(window) && (inputVertex.getVertexCount() == 0 || this->gravityButton->posInButton(inputVertex[0].position.x, inputVertex[0].position.y)))
	{
		gravityCharge = 0;
		gravityButton->setProgress(gravityCharge);
		board.enforceGravity();
		clearLines();
		checkDropOnBeat();
		this->inputVertex.clear();
		return;
	}
	else if (!isGameOver && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && inputVertex.getVertexCount() > 0)
	{
		// if it's a valid drawing input (long enough), then register as a check drop on beat
		// redundant since you do this twice in the GameBase too
		Vertex firstPoint = inputVertex[0];
		Vertex lastPoint = inputVertex[inputVertex.getVertexCount() - 1];
		int xDir = lastPoint.position.x - firstPoint.position.x;
		int yDir = lastPoint.position.y - firstPoint.position.y;
		Moving_Direction mouseDirection = Moving_Direction::UP_DIR;
		
		int XorYdir = max(abs(xDir), abs(yDir));
		if (XorYdir >= 50) // only register input if it's long enough
		{
			checkDropOnBeat();
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
	gravityCharge = 0;
	gravityButton->setProgress(gravityCharge);
}

void DropToTheBeatGame::render(RenderWindow& window)
{
	GameBase::render(window);
	renderBeatSignal(window);

	int progressBarLength = 500;
	RectangleShape progress;
	progress.setPosition(boardX, boardY + boardHeight * boardSquareSize + 30);
	progress.setOutlineColor(Color::Transparent);
	progress.setOutlineThickness(5);
	progress.setFillColor(Color(200, 200, 200));
	int checkpoint = 0;
	int remainder = 0; // percentage needed til the next checkpoint
	if (score >= threshold) // SS
	{
		checkpoint = 100;
		remainder = 1;
	}
	else if (score >= threshold * 95 / 100) // S
	{
		checkpoint = 95;
		remainder = 5;
	}
	else if (score >= threshold * 90 / 100) // A
	{
		checkpoint = 90;
		remainder = 5;
	}
	else if (score >= threshold * 85 / 100) // B
	{
		checkpoint = 85;
		remainder = 10;
	}
	else if (score >= threshold * 75 / 100) // C
	{
		checkpoint = 75;
		remainder = 10;
	}
	else if (score >= threshold * 60 / 100) // D
	{
		checkpoint = 60;
		remainder = 15;
	}
	else
	{
		checkpoint = 0;
		remainder = 60;
	}
	int thresholdRemainder = threshold * remainder / 100;
	int thresholdCheckpoint = threshold * checkpoint / 100;
	int progressScoreLeft = score - thresholdCheckpoint;
	progress.setSize(Vector2f(progressScoreLeft * progressBarLength / thresholdRemainder , 20));
	window.draw(progress);
	window.draw(assetManager->getDrawable("Whole Rank bar"));


	RectangleShape healthRect;
	healthRect.setPosition(boardX + boardWidth * boardSquareSize + 10, boardY + boardHeight * boardSquareSize * (100-health)/100);
	healthRect.setSize(Vector2f(20, boardHeight * boardSquareSize * health/ 100));
	healthRect.setFillColor(Color(211,33, 44));
	healthRect.setOutlineColor(Color(211, 33, 44));
	healthRect.setOutlineThickness(5);
	window.draw(healthRect);

	window.draw(assetManager->getDrawable("health bar"));

	text.setCharacterSize(50);
	text.setString("Combo: " + getLeftPaddingString(to_string(combo), 4, ' ') );
	text.setPosition(boardX - text.getLocalBounds().width - 100, boardY);
	window.draw(text);

	text.setFillColor(Color(255, 255, 255, 200));
	text.setString(comboString);
	text.setPosition(1024 - text.getLocalBounds().width, boardY + boardSquareSize * 5 + 75 / 2);
	if (accuracyTimer > 0)
	{
		accuracyTimer--;
		window.draw(text);
	}

	// Letter rank rendering
	text.setCharacterSize(40);
	text.setString(getRank(score, threshold));
	text.setPosition(boardX, boardY + boardHeight * boardSquareSize + 50);
	window.draw(text);

	// next rank threshold score
	text.setString(to_string(thresholdRemainder + thresholdCheckpoint));
	text.setPosition(boardX + boardWidth * boardSquareSize - text.getLocalBounds().width, boardY + boardHeight * boardSquareSize + 50);
	window.draw(text);

	this->gravityButton->render(window, text);



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

