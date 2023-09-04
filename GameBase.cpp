#include "GameBase.h"
#include "Menu.h"

GameBase::GameBase(StateManager &stateManager, string folderPath = "Tetris_theme")
	: StateScreen(stateManager), songName(fs::path(folderPath).filename().string())
{
	cout << "Initializing game" << endl;

	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);

	boardPtr = new Board(boardX, boardY);
	board = *boardPtr;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// add 2 initial 7-bags
	for (int j = 0; j < 2; j++)
	{
		vector<Type> tempTypeVector = allPieces;
		std::shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}

	// load song
	fs::path oggPath = folderPath;
	fs::path wavPath = folderPath;
	oggPath.append(oggPath.filename().string() + ".ogg");
	wavPath.append(wavPath.filename().string() + ".wav");
	if (fs::exists(oggPath))
	{
		if (!buffer.loadFromFile(oggPath.string()))
		{
			cerr << "Unable to open file " + oggPath.string() << endl;;
		}
	}
	else if (fs::exists(wavPath))
	{
		if (!buffer.loadFromFile(wavPath.string()))
		{
			cerr << "Unable to open file " + wavPath.string() << endl;;
		}
	}
	else
	{
		cerr << "Audio file doesn't exist." << endl;
		throw "Audio file doesn't exist.";
	}

	sound.setBuffer(buffer);
	currentPiecePtr = &nextPiece();
	
	loadStaticAssets();
}

GameBase::~GameBase()
{
	delete boardPtr;
	delete currentPiecePtr;
	delete holdPiecePtr;
}


void GameBase::tick(const float & dt, RenderWindow& window)
{
	if (isGameOver) return;
	std::array <int, 2> res = findNearestPossiblePlacement(window, *currentPiecePtr, board);
}

void GameBase::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	board.render(window);

	holdPiecePtr = currentPiecePtr;

	if (holdPiecePtr != nullptr)
	{
		int extra = boardSquareSize/ 2;
		if (holdPiecePtr->getType() == Type::I || holdPiecePtr->getType() == Type::O)
		{
			extra = 0;
		}
		holdPiecePtr->render(window, boardX - boardSquareSize* 4 + extra, boardY + boardSquareSize/ 2);
	}

	// Render 2 preview pieces
	int counter = 0;
	std::list<Tetromino*>::iterator fifthIt = bag.begin();
	advance(fifthIt, 2);
	for (std::list<Tetromino*>::iterator it = bag.begin(); it != fifthIt; ++it)
	{
		int extra = boardSquareSize/ 2;
		if ((*it)->getType() == Type::I || (*it)->getType() == Type::O)
		{
			extra = 0;
		}
		(*it)->render(window, boardX + (boardSquareSize/ 2) + boardSquareSize* boardWidth + extra, boardY + boardSquareSize+ boardSquareSize* 3 * counter);
		counter++;
	}


	if (clearTypeCounter > 0)
	{
		clearTypeCounter--;
		text.setString(clearTypeToString(prevClearType));
		text.setPosition(1024 - boardSquareSize* 5 - 20 - text.getLocalBounds().width, 300);
		window.draw(text);
	}

	text.setCharacterSize(60);
	text.setString(to_string(score));
	text.setPosition(boardX + boardSquareSize* boardWidth / 2 - text.getLocalBounds().width/2, boardY + boardSquareSize * boardHeight);
	window.draw(text);


	// render input
	window.draw(inputVertex);
}


void GameBase::keyEvent(const float & dt, Event event)
{
	Keyboard::Key key = event.key.code;
	map<string, Keyboard::Key> keybinds = controlsSettings->keybinds;
	if (event.type == Event::KeyPressed)
	{
		if (key == Keyboard::Escape)
		{
			reset();
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		}
		else if (key == Keyboard::R)
		{
			restart();
		}
		else if (key == keybinds["HARD_DROP"] || key == keybinds["HARD_DROP_ALT"])
		{
			keyMouseRegistered = true;
		}

	}
	else if (event.type == Event::KeyReleased)
	{
		if (key == keybinds["HARD_DROP"] || key == keybinds["HARD_DROP_ALT"])
		{
			keyMouseReleased = true;
		}
	}

	if (isGameOver) return;

	
	// No hold key control (rotation)
	if (key == keybinds["ROTATE_CW"]
		|| key == keybinds["ROTATE_CCW"]
		|| key == keybinds["HOLD"]) return;

	if ( key == keybinds["HARD_DROP"])
	{

	}

	currentKey = key;
	firstPressed = true;
}

void GameBase::clearLines()
{
	// TODO: copy board before clear, is this optimized???
	Board tempBoard = board;
	ClearingInfo tempClearingInfo = board.clearLines();
	linesCleared += tempClearingInfo.linesCleared;
	level = clamp(linesCleared / 10 + 1, 1, 15);
	ClearType tempScoresType = GameBase::determineClearType(*currentPiecePtr, tempClearingInfo, prevClearType, tempBoard);

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

void GameBase::mouseScrollEvent(Event event)
{
}

void GameBase::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	if (isGameOver)
	{
		if (event.type == Event::MouseButtonReleased && mouseInBox(window, 1024 - 150, 576 - 60 - 20, 300, 60)) // Restart button
		{
			restart();
		}
		else if (event.type == Event::MouseButtonPressed && mouseInBox(window, 1024 - 150, 576 + 20, 300, 60)) // Menu button
		{
			// reset();
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		}
	}
	else // game is still going
	{
		if (keyMouseRegistered == true || event.type == sf::Event::MouseButtonPressed)
		{
			locked = true;
			keyMouseRegistered = false;
			lastMousePos = (Mouse::getPosition(window));
		}

		if (keyMouseReleased == true || event.type == sf::Event::MouseButtonReleased)
		{
			keyMouseReleased = false;
			locked = false; // Reset
			if (inputVertex.getVertexCount() >= 2)
			{

				Vertex firstPoint = inputVertex[0];
				Vertex lastPoint = inputVertex[inputVertex.getVertexCount() - 1];
				int xDir = lastPoint.position.x - firstPoint.position.x;
				int yDir = lastPoint.position.y - firstPoint.position.y;
				Moving_Direction mouseDirection = Moving_Direction::UP_DIR;
				
				int XorYdir = max(abs(xDir), abs(yDir));
				if (XorYdir >= 50) // only register input if it's long enough
				{
					if (XorYdir == abs(xDir))// favor x direction
					{
						if (xDir > 0) // mouse move right
						{
							mouseDirection = Moving_Direction::RIGHT_DIR;
						}
						else if (xDir < 0)
						{
							mouseDirection = Moving_Direction::LEFT_DIR;
						}
					}
					else // favor y direction
					{
						if (yDir > 0)
						{
							mouseDirection = Moving_Direction::DOWN_DIR;
						}
						else if (yDir < 0)
						{
							mouseDirection = Moving_Direction::UP_DIR;
						}
					}

					int minX = -currentPiecePtr->getMinX();
					int minY = -currentPiecePtr->getMinY();
					int maxX = 9 - currentPiecePtr->getMaxX();
					int maxY = 9 - currentPiecePtr->getMaxY();
					// x - 1, y - 1 to offset to center of the piece
					int x = std::floor((firstPoint.position.x - boardX) / boardSquareSize);
					int y = std::floor((firstPoint.position.y - boardY) / boardSquareSize);

					std::cout << x << ":" << y << "=" << static_cast<int> (mouseDirection) << std::endl;

					bool possible = currentPiecePtr->setPiece(x, y, mouseDirection, board);

					if (possible) // if set piece sucessfully, move to next piece
					{
						if (prevPiecePtr != nullptr)
						{
							clearLines();
						}

						nextPiece();
					}
				}
			}
			inputVertex.clear();
		}
		
		if (locked)
        {
            if (lastMousePos != sf::Mouse::getPosition(window)) // When the Mouse hasn't moved don't add any new Vertex (save memory)
            {
				Vector2f prevMouseViewPos = window.mapPixelToCoords(lastMousePos);
				Vector2i currentMousePos = Mouse::getPosition(window);
				Vector2f mouseViewPos = window.mapPixelToCoords(currentMousePos);

				sf::Vector2f direction = mouseViewPos - prevMouseViewPos;
				sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
				sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

				sf::Vector2f offset = (inputThickness / 2.f) * unitPerpendicular;

				inputVertex.append(prevMouseViewPos + offset);
				inputVertex.append(mouseViewPos + offset);
				inputVertex.append(mouseViewPos - offset);
				inputVertex.append(prevMouseViewPos - offset);

				lastMousePos = currentMousePos;
            }
        }

	}
}

void GameBase::renderGameOver(RenderWindow& window)
{
	RectangleShape blurScreen;
	blurScreen.setPosition(0, 0);
	blurScreen.setSize(Vector2f(window.getView().getSize()));
	blurScreen.setFillColor(Color(0, 0, 0, 220));
	window.draw(blurScreen);

	createButton(window, text, Color(0, 0, 50, 255), 60, Color::White, "Restart", 300, 60, 1024 - 150, 576 - 60 - 20);
	createButton(window, text, Color(0, 0, 50, 255), 60, Color::White, "Menu", 300, 60, 1024 - 150, 576 + 20);

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
			cout << "B2B_TETRIS" << endl;
			return ClearType::B2B_TETRIS;
		}
		cout << "TETRIS" << endl;
		return ClearType::TETRIS;
		break;
	case 5:
		if (info.isPC && isB2BChainActive)
		{
			cout << "B2B_PENTRIS_PC" << endl;
			return ClearType::B2B_PENTRIS_PC;
		}
		else if (info.isPC)
		{
			cout << "TETRIS_PC" << endl;
			return ClearType::PENTRIS_PC;
		}
		else if (isB2BChainActive)
		{
			cout << "B2B_PENTRIS" << endl;
			return ClearType::B2B_PENTRIS;
		}
		cout << "PENTRIS" << endl;
		return ClearType::PENTRIS;
		break;
	default:
		cout << "NONE" << endl;
		return ClearType::NONE;
		break;
	}
}

string GameBase::clearTypeToString(ClearType clearType)
{
	return clearTypeStringMap.find(clearType)->second;
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

	alreadyHold = false;
	// If pieces have no possible move, game over
	std::array <int, 4> possibleMovesCurrent = currentPiecePtr->firstPossibleMove(board);
	if (possibleMovesCurrent[3] == 1) // if possible to place current piece
	{
	}
	else
	{
		gameOver();
	}

	return *currentPiecePtr;
}


void GameBase::hold()
{
	if (!alreadyHold)
	{
		if (holdPiecePtr != nullptr && holdPiecePtr->firstPossibleMove(board)[3] == 1) // not first hold
		{
			Tetromino* tempPiecePtr = holdPiecePtr;
			holdPiecePtr = currentPiecePtr;
			currentPiecePtr = tempPiecePtr;
		}
		else if (bag.front()->firstPossibleMove(board)[3] == 1) // first hold
		{
			holdPiecePtr = currentPiecePtr;
			nextPiece();
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

std::array<int, 2> GameBase::findNearestPossiblePlacement(RenderWindow& window, Tetromino& piece, Board& board)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	int minX = -currentPiecePtr->getMinX();
	int minY = -currentPiecePtr->getMinY();
	int maxX = 9 - currentPiecePtr->getMaxX();
	int maxY = 9 - currentPiecePtr->getMaxY();
	// x - 1, y - 1 to offset to center of the piece
	int x = std::clamp((int)std::floor((mouseViewPos.x - boardX) / boardSquareSize) - 1, -currentPiecePtr->getMinX(), 9 - currentPiecePtr->getMaxX());
	int y = std::clamp((int)std::floor((mouseViewPos.y - boardY) / boardSquareSize) - 1, -currentPiecePtr->getMinY(), 9 - currentPiecePtr->getMaxY());

	int minDistance = INT_MAX;
	int mouseMinDistance = INT_MAX;
	std::array<int, 2> res = { 0, 0 };

	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			int distance = std::pow(i - x, 2) + std::pow(j - y, 2);
			int mouseDistance = std::pow(mouseViewPos.x - (i * boardSquareSize + boardSquareSize)/ 2, 2) + std::pow(mouseViewPos.y - (j * boardSquareSize) + boardSquareSize / 2, 2);
			if (distance < minDistance && mouseDistance < mouseMinDistance && piece.checkCollision(i, j, board))
			{
				minDistance = distance;
				mouseMinDistance = mouseDistance;
				res = { i, j };
			}
		}
	}
	return res;
}

void GameBase::gameOver()
{
	isGameOver = true;
	sound.stop();
}

bool GameBase::createGarbageLine(int holePos)
{
	bool res = board.createGarbageLine(holePos);
	if (!currentPiecePtr->checkCollision(board))
	{
		currentPiecePtr->move(Moving_Direction::UP_DIR, board);

	}
	return res;
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
	if (piece.getType() == Type::T)
	{
		cout << "It's T" << std::endl;
		int x = piece.getXPos();
		int y = piece.getYPos();

		https://drive.google.com/file/d/1ev8Uo6qXt-oBwEoPyCPXUkOUkB4wh1QA/view?usp=sharing
		int ori = static_cast<int> (piece.getOrientation());
		bool leftFrontCornerFilled = ori / 2 * 2 + y >= boardHeight || (ori + 1) % 4 / 2 * 2 + x >= boardWidth || ori / 2 * 2 + y < 0 || (ori + 1) % 4 / 2 * 2 + x < 0 || board.getBoard()[ori / 2 * 2 + y][(ori + 1) % 4 / 2 * 2 + x] > 0;
		bool rightFrontCornerFilled = (ori + 1) % 4 / 2 * 2 + y >= boardHeight || (ori + 2) % 4 / 2 * 2 + x >= boardWidth || (ori + 1) % 4 / 2 * 2 + y < 0 || (ori + 2) % 4 / 2 * 2 + x < 0 || board.getBoard()[(ori + 1) % 4 / 2 * 2 + y][(ori + 2) % 4 / 2 * 2 + x] > 0;
		bool rightBackCornerFilled = (ori + 2) % 4 / 2 * 2 + y >= boardHeight || (ori + 3) % 4 / 2 * 2 + x >= boardWidth || (ori + 2) % 4 / 2 * 2 + y < 0 || (ori + 3) % 4 / 2 * 2 + x < 0 || board.getBoard()[(ori + 2) % 4 / 2 * 2 + y][(ori + 3) % 4 / 2 * 2 + x] > 0;
		bool leftBackCornerFilled = (ori + 3) % 4 / 2 * 2 + y >= boardHeight || ori / 2 * 2 + x >= boardWidth || (ori + 3) % 4 / 2 * 2 + y < 0 || ori / 2 * 2 + x < 0 || board.getBoard()[(ori + 3) % 4 / 2 * 2 + y][ori / 2 * 2 + x] > 0;

		if (leftFrontCornerFilled && rightFrontCornerFilled && (rightBackCornerFilled || leftBackCornerFilled))
		{
			return 2;
			cout << "It's T2" << std::endl;
		}
		else if (rightBackCornerFilled && leftBackCornerFilled && (leftFrontCornerFilled || rightFrontCornerFilled))
		{
			cout << "It's T1" << std::endl;
			return 1;
		}
	}
	return 0;
}

