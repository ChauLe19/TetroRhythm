#include "GameBase.h"

GameBase::GameBase(Controls_Settings& settings)
	: settings(settings), delayAutoShift(settings.delayAutoShift),
	autoRepeatRate(settings.autoRepeatRate), keybinds(settings.keybinds)
{
	cout << "Initializing game" << endl;

	font.loadFromFile("Dense-Regular.otf");
	text.setFont(font);
	text.setFillColor(Color::White);

	boardPtr = new Board(boardX, boardY);
	board = *boardPtr;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// add 2 initial 7-bags
	for (int j = 0; j < 2; j++)
	{
		vector<Type> tempTypeVector = allPieces;
		shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}

	// Load map info
	string txtFile = "output.txt";
	//string txtFile = "Tetris_theme.txt";
	string musicFile = "Tetris_theme.ogg";
	inFile.open(txtFile);
	if (!inFile)
	{
		cerr << "Unable to open file " + txtFile << endl;;
	}


	char beat[10];
	while (inFile.getline(beat, 10, '\r'))
	{
		beatsTime.push_back(atoi(beat));
	}
	beatIt = beatsTime.begin();
	nextBeatTimeMS = *beatIt;

	if (!buffer.loadFromFile(musicFile))
	{
		cerr << "Unable to open file " + musicFile << endl;;
	}
	sound.setBuffer(buffer);


	currentPiecePtr = &nextPiece();
}

GameBase::GameBase(Controls_Settings& settings, string folderPath)
	: settings(settings), delayAutoShift(settings.delayAutoShift),
	autoRepeatRate(settings.autoRepeatRate), keybinds(settings.keybinds)
{
	cout << "Initializing game" << endl;

	font.loadFromFile("Dense-Regular.otf");
	text.setFont(font);
	text.setFillColor(Color::White);

	boardPtr = new Board(boardX, boardY);
	board = *boardPtr;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// add 2 initial 7-bags
	for (int j = 0; j < 2; j++)
	{
		vector<Type> tempTypeVector = allPieces;
		shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}


	fs::path audioPath = folderPath;
	audioPath.append(audioPath.filename().string() + ".ogg");
	cout << "Beat map editor" << endl;
	if (!fs::exists(audioPath))
	{
		audioPath = audioPath.parent_path();
		audioPath.append(audioPath.filename().string() + ".wav");
		if (!fs::exists(audioPath))
			cerr << "Audio file doesn't exist." << endl;
	}

	fs::path txtPath = folderPath;
	txtPath.append(txtPath.filename().string() + ".txt");

	if (!fs::exists(txtPath))
		cerr << "Text file doesn't exist." << endl;

	// Load map info
	string txtFile = fs::absolute(txtPath).string();
	//string txtFile = "Tetris_theme.txt";
	string musicFile = fs::absolute(audioPath).string();

	cout << txtFile << endl;
	cout << musicFile << endl;
	inFile.open(txtFile);
	if (!inFile)
	{
		cerr << "Unable to open file " + txtFile << endl;;
	}


	char beat[10];
	while (inFile.getline(beat, 10, '\r'))
	{
		beatsTime.push_back(atoi(beat));
	}
	beatIt = beatsTime.begin();
	nextBeatTimeMS = *beatIt;

	if (!buffer.loadFromFile(musicFile))
	{
		cerr << "Unable to open file " + musicFile << endl;;
	}
	sound.setBuffer(buffer);


	currentPiecePtr = &nextPiece();
}

GameBase::~GameBase()
{
	delete boardPtr;
	delete currentPiecePtr;
	delete holdPiecePtr;
}

void GameBase::tick(State& state, RenderWindow& window)
{
	if (isGameOver) return;


	if (Keyboard::isKeyPressed(keybinds["SOFT_DROP"]))
	{
		//cout << "DAS count:" << delayAutoShiftCount << endl;
		if (SDfirstPressed)
		{
			SDfirstPressed = false;
			SDisAutoRepeatActive = false;
			SDisAutoShiftActive = true;
			SDdelayAutoShiftCount = 0;
			SDautoRepeatRateCount = 0;
			if (currentPiecePtr->move(Moving_Direction::DOWN_DIR, board))
				score += GameBase::convertClearTypeToScores(ClearType::SOFTDROP);
		}
		else if (isAutoShiftActive)
		{
			SDdelayAutoShiftCount++;
			if (SDdelayAutoShiftCount >= 6)
			{
				SDisAutoRepeatActive = true;
				SDisAutoShiftActive = false;
			}
		}
		else if (isAutoRepeatActive)
		{
			//SD arr = 1
			if (SDautoRepeatRateCount < 1)
			{
				SDautoRepeatRateCount++;
			}
			else
			{
				SDautoRepeatRateCount = 0;

				if (currentPiecePtr->move(Moving_Direction::DOWN_DIR, board))
					score += GameBase::convertClearTypeToScores(ClearType::SOFTDROP);
			}
		}
	}
	else // not holding soft drop
	{
		SDdelayAutoShiftCount = 0;
		SDautoRepeatRateCount = 0;
		SDisAutoRepeatActive = false;
		SDisAutoShiftActive = false;
	}


	// Left right DAS & ARR
	if (Keyboard::isKeyPressed(currentKey))
	{
		//cout << "DAS count:" << delayAutoShiftCount << endl;
		if (firstPressed)
		{
			firstPressed = false;
			isAutoRepeatActive = false;
			isAutoShiftActive = true;
			delayAutoShiftCount = 0;
			autoRepeatRateCount = 0;
		}
		else if (isAutoShiftActive)
		{
			delayAutoShiftCount++;
			if (delayAutoShiftCount >= delayAutoShift)
			{
				isAutoRepeatActive = true;
				isAutoShiftActive = false;
			}
			return;
		}
		else if (isAutoRepeatActive)
		{
			if (autoRepeatRateCount < autoRepeatRate)
			{
				autoRepeatRateCount++;
				return;
			}
			else
			{
				autoRepeatRateCount = 0;
			}
		}
	}
	else // not holding
	{
		delayAutoShiftCount = 0;
		autoRepeatRateCount = 0;
		isAutoRepeatActive = false;
		isAutoShiftActive = false;
		return;
	}

	if (currentKey == keybinds["MOVE_RIGHT"])
	{
		if (isAutoRepeatActive && autoRepeatRate == 0)
			while (currentPiecePtr->move(Moving_Direction::RIGHT_DIR, board));
		else
			currentPiecePtr->move(Moving_Direction::RIGHT_DIR, board);
	}
	else if (currentKey == keybinds["MOVE_LEFT"])
	{
		if (isAutoRepeatActive && autoRepeatRate == 0)
			while (currentPiecePtr->move(Moving_Direction::LEFT_DIR, board));
		else
			currentPiecePtr->move(Moving_Direction::LEFT_DIR, board);
	}



	//TODO: separate das & arr for soft drop


}

void GameBase::render(RenderWindow& window)
{


	board.render(window);
	currentPiecePtr->render(window, board);
	currentPiecePtr->getGhost(board).render(window, board);
	if (holdPiecePtr != nullptr)
	{
		int extra = squareSize / 2;
		if (holdPiecePtr->getType() == Type::I)
		{
			extra = 0;
		}
		else if (holdPiecePtr->getType() == Type::O)
		{
			extra = 36;
		}
		holdPiecePtr->render(window, boardX - (squareSize / 2 + 20) - squareSize * 4 + extra, boardY + squareSize / 2);
	}

	// Render 5 preview pieces
	int counter = 0;
	std::list<Tetromino*>::iterator fifthIt = bag.begin();
	advance(fifthIt, 5);
	for (std::list<Tetromino*>::iterator it = bag.begin(); it != fifthIt; ++it)
	{
		int extra = squareSize / 2;
		if ((*it)->getType() == Type::I)
		{
			extra = 0;
		}
		else if ((*it)->getType() == Type::O)
		{
			extra = squareSize;
		}
		(*it)->render(window, boardX + (squareSize / 2 + 20) + squareSize * 10 + extra, boardY + squareSize + squareSize * 3 * counter);
		counter++;
	}


	//int endYPos = 100 + 18*20;
	/*int endYPos = 120;
	text.setString("--------------------------------");
	text.setPosition(300, endYPos);
	window.draw(text);*/



	if (clearTypeCounter > 0)
	{
		clearTypeCounter--;
		text.setString(clearTypeToString(prevClearType));
		text.setPosition(700, 300);
		window.draw(text);
		text.setString(to_string(convertClearTypeToScores(prevClearType)));
		text.setPosition(700, 350);
		window.draw(text);
	}

	text.setString(to_string(score));
	text.setPosition(100, 0);
	window.draw(text);

	if (isGameOver)
	{
		text.setString("GAME OVER");
		text.setPosition(300, 0);
		window.draw(text);
		text.setString("Press R to restart");
		text.setPosition(270, 20);
		window.draw(text);
	}
}


void GameBase::keyEvent(State& state, Keyboard::Key key)
{
	if (key == Keyboard::Escape)
	{
		reset();
		state = State::MENU;
	}
	else if (key == Keyboard::R)
	{
		restart();
	}

	if (isGameOver) return;

	if (key == keybinds["ROTATE_CW"])
	{
		currentPiecePtr->rotate(Rotational_Direction::CW, board);
	}
	else if (key == keybinds["ROTATE_CCW"])
	{
		currentPiecePtr->rotate(Rotational_Direction::CCW, board);
	}
	else if (key == keybinds["ROTATE_180"])
	{
		currentPiecePtr->rotate(Rotational_Direction::R180, board);
	}
	else if (key == keybinds["HARD_DROP"])
	{
		currentPiecePtr->hardDrop(board);
		//cout << "input" << endl;
		//board.print();
		score += GameBase::convertClearTypeToScores(ClearType::HARDDROP);

		nextPiece();

		//alreadyHold = false;
		onGroundCount = 0;
		frameCount = 0;

		if (prevPiecePtr != nullptr)
		{
			//cout << "Clearing" << endl;
			// TODO: copy board before clear, is this optimized???
			Board tempBoard = board;
			ClearingInfo tempClearingInfo = board.clearLines();
			linesCleared += tempClearingInfo.linesCleared;
			level = clamp(linesCleared / 10 + 1, 1, 15);
			ClearType tempScoresType = GameBase::determineClearType(*prevPiecePtr, tempClearingInfo, prevClearType, tempBoard);

			//update clear type everytime the play drop a piece
			recentClearType = tempScoresType;

			//update clear type only when the dropped piece clear lines
			// ignore if not clearing anything. maintain b2b after a clearing-nothing hard drop
			if (tempScoresType != ClearType::NONE)
			{
				prevClearType = tempScoresType;
				clearTypeCounter = 60; // 1 second display
			}
			score += GameBase::convertClearTypeToScores(tempScoresType);
		}


	}
	else if (key == keybinds["HOLD"])
	{
		hold();
	}
	else if (key == Keyboard::P)
	{
		cout << "playing:" << sound.getPlayingOffset().asMilliseconds() << endl;
	}

	
	// No hold key control (rotation)
	if (key == keybinds["ROTATE_CW"]
		|| key == keybinds["ROTATE_CCW"]
		|| key == keybinds["HARD_DROP"]
		|| key == keybinds["HOLD"]) return;

	currentKey = key;
	firstPressed = true;
	isAutoShiftActive = false;
}

void GameBase::mouseEvent(State& state, RenderWindow& window)
{
}

void GameBase::renderBeatSignal(RenderWindow& window)
{
	//static vector<Color> rainbow = { Color::Red, Color(255, 165, 0), Color::Yellow, Color::Green, Color::Blue, Color(75,0,130) ,Color(127,0,255) };
	//int tempRainbowIndex = rainbowIndex;


	//int maxRectOffset = 50;
	//int nowTime = sound.getPlayingOffset().asMilliseconds();
	//std::list<Tetromino*>::iterator it = bag.begin();
	//list<int>::iterator tempBeatIt = beatIt; // copy beatIt to tempBeatsIt
	//for (std::list<Tetromino*>::iterator it = bag.begin(); it != bag.end() && tempBeatIt != beatsTime.end(); ++it, ++tempBeatIt, ++tempRainbowIndex)
	//{
	//	int bufferTime = *tempBeatIt;
	//	int distanceFromEnd = (bufferTime - nowTime) / 32;// (1 / 60 second per frame)*1000 milisec per sec

	//	if (distanceFromEnd > maxRectOffset) break;

	//	//draw outer rect border (beat)
	//	sf::RectangleShape rectangle;
	//	rectangle.setSize(sf::Vector2f(squareSize * 10 + distanceFromEnd * 4, squareSize * 20 + distanceFromEnd * 4));
	//	rectangle.setFillColor(Color(0, 0, 0, 0));
	//	rectangle.setOutlineColor(rainbow.at(tempRainbowIndex % 7));
	//	rectangle.setOutlineThickness(5);
	//	rectangle.setPosition(boardX - distanceFromEnd * 2, boardY - distanceFromEnd * 2);
	//	window.draw(rectangle);

	//}

	static vector<Color> rainbow = { Color::Red, Color(255, 165, 0), Color::Yellow, Color::Green, Color::Blue, Color(75,0,130) ,Color(127,0,255) };
	int tempRainbowIndex = rainbowIndex;

	const int innerRadius = 75;
	CircleShape circle;
	circle.setRadius(innerRadius);
	circle.setPosition(Vector2f(1024 - innerRadius, 200));
	circle.setFillColor(Color(100, 100, 100,150));
	circle.setOutlineColor(Color(200, 200, 200, 150));
	circle.setOutlineThickness(5);
	window.draw(circle);

	int maxOffsetMS = 2000;
	int nowTime = sound.getPlayingOffset().asMilliseconds();
	std::list<Tetromino*>::iterator it = bag.begin();
	list<int>::iterator tempBeatIt = beatIt; // copy beatIt to tempBeatsIt

	for (std::list<Tetromino*>::iterator it = bag.begin(); it != bag.end() && tempBeatIt != beatsTime.end(); ++it, ++tempBeatIt, ++tempRainbowIndex)
	{
		int bufferTime = *tempBeatIt;
		int timeOffset = bufferTime - nowTime;// (1 / 60 second per frame)*1000 milisec per sec

		if (timeOffset > maxOffsetMS) break;
		if (prevBeatTimeMS >= bufferTime) continue;
		int distanceFromEnd = timeOffset / 20;
		CircleShape circle;
		circle.setRadius(75 + distanceFromEnd);
		circle.setPosition(Vector2f(1024 - (innerRadius + distanceFromEnd), 200 - distanceFromEnd));
		circle.setFillColor(Color::Transparent);
		circle.setOutlineColor(Color(200, 200, 200, 200));
		circle.setOutlineThickness(5);
		window.draw(circle);

		//draw outer rect border (beat)
		//sf::RectangleShape rectangle;
		//rectangle.setSize(sf::Vector2f(squareSize * 10 + distanceFromEnd * 4, squareSize * 20 + distanceFromEnd * 4));
		//rectangle.setFillColor(Color(0, 0, 0, 0));
		//rectangle.setOutlineColor(rainbow.at(tempRainbowIndex % 7));
		//rectangle.setOutlineThickness(5);
		//rectangle.setPosition(boardX - distanceFromEnd * 2, boardY - distanceFromEnd * 2);
		//window.draw(rectangle);

	}

}

int GameBase::convertClearTypeToScores(ClearType type)
{
	return clearTypeScore[static_cast<int>(type)];
}

ClearType GameBase::determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType, Board board)
{
	bool isB2BChainActive = isB2BChain(prevClearType);

	int tspinType = getTSpinType(clearingPiece, board);
	switch (info.linesCleared)
	{
	case 0:
		if (tspinType == 1)
		{
			cout << "TSPIN_MINI_NO" << endl;
			return ClearType::TSPIN_MINI_NO;
		}
		else if (tspinType == 2)
		{
			cout << "TSPIN_NO" << endl;
			return ClearType::TSPIN_NO;
		}
		cout << "NONE" << endl;
		return ClearType::NONE;
		break;
	case 1:
		if (info.isPC)
		{
			cout << "SINGLE_LINE_PC" << endl;
			return ClearType::SINGLE_LINE_PC;
		}
		if (isB2BChainActive)
		{
			if (tspinType == 1)
			{
				cout << "B2B_TSPIN_MINI_SINGLE" << endl;
				return ClearType::B2B_TSPIN_MINI_SINGLE;
			}
			else if (tspinType == 2)
			{
				cout << "B2B_TSPIN_SINGLE" << endl;
				return ClearType::B2B_TSPIN_SINGLE;
			}
		}
		else
		{
			if (tspinType == 1)
			{
				cout << "TSPIN_MINI_SINGLE" << endl;
				return ClearType::TSPIN_MINI_SINGLE;
			}
			else if (tspinType == 2)
			{
				cout << "TSPIN_SINGLE" << endl;
				return ClearType::TSPIN_SINGLE;
			}
		}
		cout << "SINGLE" << endl;
		return ClearType::SINGLE;
		break;
	case 2:
		if (info.isPC)
		{
			cout << "DOUBLE_LINE_PC" << endl;
			return ClearType::DOUBLE_LINE_PC;
		}
		if (isB2BChainActive)
		{
			if (tspinType == 1)
			{
				cout << "B2B_TSPIN_MINI_DOUBLE" << endl;
				return ClearType::B2B_TSPIN_MINI_DOUBLE;
			}
			else if (tspinType == 2)
			{
				cout << "B2B_TSPIN_DOUBLE" << endl;
				return ClearType::B2B_TSPIN_DOUBLE;
			}
		}
		else
		{
			if (tspinType == 1)
			{
				cout << "TSPIN_MINI_DOUBLE" << endl;
				return ClearType::TSPIN_MINI_DOUBLE;
			}
			else if (tspinType == 2)
			{
				cout << "TSPIN_DOUBLE" << endl;
				return ClearType::TSPIN_DOUBLE;
			}
		}
		cout << "DOUBLE" << endl;
		return ClearType::DOUBLE;
		break;
	case 3:
		if (info.isPC)
		{
			cout << "TRIPLE_LINE_PC" << endl;
			return ClearType::TRIPLE_LINE_PC;
		}
		if (isB2BChainActive && tspinType > 0)
		{
			cout << "B2B_TSPIN_TRIPLE" << endl;
			return ClearType::B2B_TSPIN_TRIPLE;
		}
		else if (tspinType > 0)
		{
			cout << "TSPIN_TRIPLE" << endl;
			return ClearType::TSPIN_TRIPLE;
		}
		cout << "TRIPLE" << endl;
		return ClearType::TRIPLE;
		break;
	case 4:
		if (info.isPC && isB2BChainActive)
		{
			cout << "B2B_TETRIS_PC" << endl;
			return ClearType::B2B_TETRIS_PC;
		}
		else if (info.isPC)
		{
			cout << "TETRIS_PC" << endl;
			return ClearType::TETRIS_PC;
		}
		else if (isB2BChainActive)
		{
			cout << "B2B B2B_TETRIS" << endl;
			return ClearType::B2B_TETRIS;
		}
		cout << "TETRIS" << endl;
		return ClearType::TETRIS;
		break;
	default:
		cout << "NONE" << endl;
		return ClearType::NONE;
		break;
	}
}

string GameBase::clearTypeToString(ClearType clearType)
{
	switch (clearType)
	{
	case ClearType::NONE:
		return "None";
		break;
	case ClearType::SINGLE:
		return "Single";
		break;
	case ClearType::DOUBLE:
		return "Double";
		break;
	case ClearType::TRIPLE:
		return "Triple";
		break;
	case ClearType::TETRIS:
		return "Tetris";
		break;
	case ClearType::TSPIN_MINI_NO:
		return "T-Spin Mini";
		break;
	case ClearType::TSPIN_MINI_SINGLE:
		return "T-Spin Mini Single";
		break;
	case ClearType::TSPIN_SINGLE:
		return "T-Spin Single";
		break;
	case ClearType::TSPIN_MINI_DOUBLE:
		return "T-Spin Mini Double";
		break;
	case ClearType::TSPIN_DOUBLE:
		return "T-Spin Double";
		break;
	case ClearType::TSPIN_TRIPLE:
		return "T-Spin Triple";
		break;
	case ClearType::COMBO:
		return "Combo";
		break;
	case ClearType::SOFTDROP:
		return "Soft Drop";
		break;
	case ClearType::HARDDROP:
		return "Hard Drop";
		break;
	case ClearType::SINGLE_LINE_PC:
		return "Single-Line PC";
		break;
	case ClearType::DOUBLE_LINE_PC:
		return "Double-Line PC";
		break;
	case ClearType::TRIPLE_LINE_PC:
		return "Triple-Line PC";
		break;
	case ClearType::TETRIS_PC:
		return "Tetris PC";
		break;
	case ClearType::B2B_TETRIS_PC:
		return "B2B Tetris PC";
		break;
	case ClearType::B2B_TETRIS:
		return "B2B Tetris";
		break;
	case ClearType::B2B_TSPIN_MINI_SINGLE:
		return "B2B T-Spin Mini Single";
		break;
	case ClearType::B2B_TSPIN_SINGLE:
		return "B2B T-Spin Single";
		break;
	case ClearType::B2B_TSPIN_MINI_DOUBLE:
		return "B2B T-Spin Mini Double";
		break;
	case ClearType::B2B_TSPIN_DOUBLE:
		return "B2B T-Spin Double";
		break;
	case ClearType::B2B_TSPIN_TRIPLE:
		return "B2B T-Spin Triple";
		break;
	default:
		return "INVALID";
		break;
	}
}

Tetromino& GameBase::nextPiece()
{
	// Take out a tetromino from the bag
	prevPiecePtr = currentPiecePtr;
	currentPiecePtr = bag.front();
	bag.pop_front();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// If bag has less than or equal to 7,
	// add in a shuffled bag of all pieces into current bag.
	if (bag.size() <= 7)
	{
		vector<Type> tempTypeVector = allPieces;
		shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}

	// If piece spawn collide right away, game over
	if (!currentPiecePtr->checkCollision(board)) gameOver();

	alreadyHold = false;
	return *currentPiecePtr;
}


void GameBase::hold()
{
	if (!alreadyHold)
	{
		if (holdPiecePtr == nullptr)
		{
			holdPiecePtr = currentPiecePtr;
			//currentPiecePtr = &nextPiece();
			nextPiece();
		}
		else
		{
			Tetromino* tempPiecePtr = holdPiecePtr;
			holdPiecePtr = currentPiecePtr;
			currentPiecePtr = tempPiecePtr;
		}
		holdPiecePtr->reset();
		alreadyHold = true;
	}
}

void GameBase::pause()
{
	sound.pause();
}

void GameBase::start()
{
	sound.play();
}

void GameBase::reset()
{
	delete boardPtr;
	delete currentPiecePtr;
	delete prevPiecePtr;
	delete holdPiecePtr;

	boardPtr = new Board(boardX, boardY);
	board = *boardPtr;
	currentPiecePtr = nullptr;
	prevPiecePtr = nullptr;
	holdPiecePtr = nullptr;
	prevClearType = ClearType::NONE;
	onGroundCount = 0;
	score = 0;
	isGameOver = false;
	alreadyHold = false;
	inFile.clear();

	beatIt = beatsTime.begin();
	nextBeatTimeMS = *beatIt;
	prevBeatTimeMS = 0;
	bag.clear();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// add 2 initial 7-bags
	for (int j = 0; j < 2; j++)
	{
		vector<Type> tempTypeVector = allPieces;
		shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}

	sound.stop();
	sound.setPlayingOffset(seconds(0));

	currentPiecePtr = &nextPiece();
}

void GameBase::restart()
{
	reset();
	start();
}

int GameBase::getScore()
{
	return score;
}

void GameBase::gameOver()
{
	isGameOver = true;
	sound.stop();
}


bool GameBase::isB2BChain(ClearType type)
{
	switch (type)
	{
	case ClearType::TSPIN_MINI_NO:
	case ClearType::TSPIN_NO:
	case ClearType::TSPIN_MINI_SINGLE:
	case ClearType::TSPIN_SINGLE:
	case ClearType::TSPIN_MINI_DOUBLE:
	case ClearType::TSPIN_DOUBLE:
	case ClearType::TSPIN_TRIPLE:
	case ClearType::TETRIS:
	case ClearType::B2B_TETRIS:
	case ClearType::B2B_TSPIN_MINI_SINGLE:
	case ClearType::B2B_TSPIN_SINGLE:
	case ClearType::B2B_TSPIN_MINI_DOUBLE:
	case ClearType::B2B_TSPIN_DOUBLE:
	case ClearType::B2B_TSPIN_TRIPLE:
		return true;
		break;
	default:
		return false;
		break;
	}
}


// 0: not a t-spin of any kind
// 1: mini t-spin
// 2: t-spin double
int GameBase::getTSpinType(Tetromino piece, Board& board)
{
	if (piece.getType() == Type::T && piece.getRotateLast())
	{
		int x = piece.getXPos();
		int y = piece.getYPos();

	https://drive.google.com/file/d/1ev8Uo6qXt-oBwEoPyCPXUkOUkB4wh1QA/view?usp=sharing
		int ori = static_cast<int> (piece.getOrientation());
		bool leftFrontCornerFilled = ori / 2 * 2 + y >= boardHeight || (ori + 1) % 4 / 2 * 2 + x >= boardWidth || board.getBoard()[ori / 2 * 2 + y][(ori + 1) % 4 / 2 * 2 + x] > 0;
		bool rightFrontCornerFilled = (ori + 1) % 4 / 2 * 2 + y >= boardHeight || (ori + 2) % 4 / 2 * 2 + x >= boardWidth || board.getBoard()[(ori + 1) % 4 / 2 * 2 + y][(ori + 2) % 4 / 2 * 2 + x] > 0;
		bool rightBackCornerFilled = (ori + 2) % 4 / 2 * 2 + y >= boardHeight || (ori + 3) % 4 / 2 * 2 + x >= boardWidth || board.getBoard()[(ori + 2) % 4 / 2 * 2 + y][(ori + 3) % 4 / 2 * 2 + x] > 0;
		bool leftBackCornerFilled = (ori + 3) % 4 / 2 * 2 + y >= boardHeight || ori / 2 * 2 + x >= boardWidth || board.getBoard()[(ori + 3) % 4 / 2 * 2 + y][ori / 2 * 2 + x] > 0;

		if (leftFrontCornerFilled && rightFrontCornerFilled && (rightBackCornerFilled || leftBackCornerFilled))
		{
			return 2;
		}
		else if (rightBackCornerFilled && leftBackCornerFilled && (leftFrontCornerFilled || rightFrontCornerFilled))
		{
			return 1;
		}
	}
	return 0;
}

