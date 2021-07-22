#include "GameBase.h"

GameBase::GameBase()
{
	cout << "Initializing game" << endl;
	//board = Board(boardX, boardY);
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

	currentPiecePtr = &nextPiece();
	string txtFile = "Tetris_theme.txt";
	string musicFile = "Tetris_theme.wav";
	inFile.open(txtFile);
	if (!inFile)
	{
		cerr << "Unable to open file " + txtFile << endl;;
	}
	char beat[10];
	inFile.getline(beat, 10,'\r');
	nextBeatTimeMS = atoi(beat);
	cout << "First beat:" << nextBeatTimeMS << endl;
	if (!buffer.loadFromFile(musicFile))
	{
		cerr << "Unable to open file " + musicFile << endl;;
	}
	sound.setBuffer(buffer);
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

Tetromino& GameBase::nextPiece()
{
	prevPiecePtr = currentPiecePtr;
	currentPiecePtr = bag.front();
	bag.pop_front();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
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
	if (!currentPiecePtr->checkCollision(board)) gameOver();

	alreadyHold = false;
	return *currentPiecePtr;
}

void GameBase::increaseOnGroundCount()
{
	onGroundCount++;
}


int GameBase::convertClearTypeToScores(ClearType type)
{
	return clearTypeScore[static_cast<int>(type)];
}




bool GameBase::getIsGameOver()
{
	return isGameOver;
}

bool isB2BChain(ClearType type)
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
int getTSpinType(Tetromino piece, Board& board)
{
	if (piece.getType() == Type::T && piece.getRotateLast())
	{
		int x = piece.getXPos();
		int y = piece.getYPos();
		int ori = static_cast<int> (piece.getOrientation());
		bool leftFrontCornerFilled = ori / 2 * 2 + y >= boardHeight || (ori + 1) % 4 / 2 * 2 + x >= boardWidth || board.getBoard()[ori / 2 * 2 + y][(ori + 1) % 4 / 2 * 2 + x] > 0;
		bool rightFrontCornerFilled = (ori + 1) % 4 / 2 * 2 + y >= boardHeight || (ori + 2) % 4 / 2 * 2 + x >= boardWidth || board.getBoard()[(ori + 1) % 4 / 2 * 2 + y][(ori + 2) % 4 / 2 * 2 + x] > 0;
		bool rightBackCornerFilled = (ori + 2) % 4 / 2 * 2 + y >= boardHeight || (ori + 3) % 4 / 2 * 2 + x >= boardWidth || board.getBoard()[(ori + 2) % 4 / 2 * 2 + y][(ori + 3) % 4 / 2 * 2 + x] > 0;
		bool leftBackCornerFilled = (ori + 3) % 4 / 2 * 2 + y >= boardHeight || ori / 2 * 2 + x >= boardWidth || board.getBoard()[(ori + 3) % 4 / 2 * 2 + y][ori / 2 * 2 + x] > 0;
		// cout << "LF:" << leftFrontCornerFilled << "\tRF:" << rightFrontCornerFilled << "\tLB:" << leftBackCornerFilled << "\tRB:" << rightBackCornerFilled << endl;
		// cout << "LF:" << ori / 2 * 2 + y << '+' << (ori + 1) % 4 / 2 * 2 + x
		// 	<< "\tRF:" << (ori + 1) % 4 / 2 * 2 + y << '+' << (ori + 2) % 4 / 2 * 2 + x
		// 	<< "\tLB:" << (ori + 2) % 4 / 2 * 2 + y << '+' << (ori + 3) % 4 / 2 * 2 + x
		// 	<< "\tRB:" << (ori + 3) % 4 / 2 * 2 + y << '+' << ori / 2 * 2 + x << endl;
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



int GameBase::getScore()
{
	return score;
}

void GameBase::render(RenderWindow& window)
{
	board.render(window);
	currentPiecePtr->render(window, board);
	currentPiecePtr->getGhost(board).render(window, board);
	if (holdPiecePtr != nullptr)
		holdPiecePtr->render(window, 50, 100);
	int counter = 0;
	std::list<Tetromino*>::iterator fifthIt = bag.begin();
	advance(fifthIt, 5);
	for (std::list<Tetromino*>::iterator it = bag.begin(); it != fifthIt; ++it)
	{
		(*it)->render(window, 300, 100 + 50 * counter);
		counter++;
	}
}

Tetromino* GameBase::getCurrentPiecePtr()
{
	return currentPiecePtr;
}

Tetromino* GameBase::getPrevPiecePtr()
{
	return prevPiecePtr;
}
Tetromino& GameBase::getCurrentPiece()
{
	return *currentPiecePtr;
}
Tetromino& GameBase::getPrevPiece()
{
	return *prevPiecePtr;
}
void GameBase::setPrevPiecePtr(Tetromino* piece)
{
	prevPiecePtr =  piece;
}
void GameBase::setCurrentPiecePtr(Tetromino* piece)
{
	currentPiecePtr =  piece;
}

ClearType GameBase::getPrevClearType()
{
	return prevClearType;
}

void GameBase::setPrevClearType(ClearType type)
{
	prevClearType = type;
}

Board& GameBase::getBoard()
{
	return board;
}

//Board* Game::getBoardPtr()
//{
//	return boardPtr;
//}

void GameBase::resetOnGroundCount()
{
	onGroundCount = 0;
}

void GameBase::setScore(int score)
{
	this->score = score;
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
	boardPtr = new Board(boardX, boardY);
	board = *boardPtr;
	currentPiecePtr = nullptr;
	prevPiecePtr = nullptr;
	holdPiecePtr = nullptr;
	onGroundCount = 0;
	prevClearType = ClearType::NONE;
	score = 0;
	isGameOver = false;
	alreadyHold = false;
	inFile.clear();
	inFile.seekg(0); 
	char beat[10];
	inFile.getline(beat, 10, '\r');
	nextBeatTimeMS = atoi(beat);
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
	currentPiecePtr = &nextPiece();
	sound.stop();
	sound.setPlayingOffset(seconds(0));
}
void GameBase::restart()
{
	reset();
	start();
}
Sound& GameBase::getSound()
{
	return sound;
}

void GameBase::gameOver()
{
	isGameOver = true;
	sound.stop();
	sound.setPlayingOffset(seconds(0));
}

GameBase::~GameBase()
{
	delete currentPiecePtr;
	delete holdPiecePtr;
}



