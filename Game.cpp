#include "Game.h"

Game::Game()
{
	cout << "Initializing game" << endl;
	//board = Board(boardX, boardY);
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

}

void Game::hold()
{
	if (!alreadyHold)
	{
		if (holdPiecePtr == nullptr)
		{
			holdPiecePtr = currentPiecePtr;
			currentPiecePtr = &nextPiece();
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

Tetromino& Game::nextPiece()
{
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
	cout << endl;


	return *currentPiecePtr;
}


int convertClearTypeToScores(ClearType type)
{
	return clearTypeScore[static_cast<int>(type)];
}


void Game::tick(RenderWindow& window)
{
	frameCount++;
	Event event;
	if (frameCount >= 48)
	{
		currentPiecePtr->move(Moving_Direction::DOWN_DIR, board);
		frameCount = 0;
	}
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case Keyboard::F:
				currentPiecePtr->rotate(Rotational_Direction::CW, board);
				break;
			case Keyboard::A:
				currentPiecePtr->rotate(Rotational_Direction::CCW, board);
				break;
			case Keyboard::S:
				currentPiecePtr->rotate(Rotational_Direction::R180, board);
				break;
			case Keyboard::L:
				currentPiecePtr->move(Moving_Direction::RIGHT_DIR, board);
				break;
			case Keyboard::J:
				currentPiecePtr->move(Moving_Direction::LEFT_DIR, board);
				break;
			case Keyboard::K:
				if (currentPiecePtr->move(Moving_Direction::DOWN_DIR, board)) score += convertClearTypeToScores(ClearType::SOFTDROP);
				break;
			case Keyboard::I:
				currentPiecePtr->hardDrop(board);
				score += convertClearTypeToScores(ClearType::HARDDROP);
				//currentPiece = nextPiece();
				prevPiecePtr = currentPiecePtr;
				currentPiecePtr = &nextPiece();
				currentPiecePtr->checkIsOnGround(board);
				alreadyHold = false;
				onGroundCount = 0;
				break;
			case Keyboard::D:
				hold();
				break;
			}
			if (prevPiecePtr != nullptr)
			{
				// TODO: copy board before clear, is this optimized???
				Board tempBoard = board;
				ClearingInfo tempClearingInfo = board.clearLines();
				ClearType tempScoresType = determineClearType(*prevPiecePtr, tempClearingInfo, prevClearType, board);
				if (tempScoresType != ClearType::NONE)
				{
					prevClearType = tempScoresType;
				}
				score += convertClearTypeToScores(tempScoresType);
			}
		}
	}
	if (currentPiecePtr->getIsOnGround(board))
	{
		onGroundCount++;
		if (onGroundCount > 100)
		{
			currentPiecePtr->hardDrop(board);
			// TODO: copy board before clear, is this optimized???
			Board tempBoard = board;
			prevPiecePtr = currentPiecePtr;
			ClearingInfo tempClearingInfo = board.clearLines();
			ClearType tempScoresType = determineClearType(*prevPiecePtr, tempClearingInfo, prevClearType, tempBoard);

			if (tempScoresType != ClearType::NONE)
			{
				prevClearType = tempScoresType;
			}
			score += convertClearTypeToScores(tempScoresType);
			currentPiecePtr = &nextPiece();
			alreadyHold = false;
			onGroundCount = 0;
		}
	}
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

ClearType Game::determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType, Board board)
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



int Game::getScore()
{
	return score;
}

void Game::render(RenderWindow& window)
{
	board.render(window);
	currentPiecePtr->render(window, board);
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

Game::~Game()
{
	delete currentPiecePtr;
	delete holdPiecePtr;
}



