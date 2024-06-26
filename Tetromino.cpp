#include "Tetromino.h"
#include "AssetManager.h"

Tetromino::Tetromino(Type type)
{
	this->type = type;
	cellImage.setTexture(AssetManager::getInstance()->getTexture("tiles"));
	int halfSquareSize = squareSize / 2;
	cellImage.setTextureRect(sf::IntRect(static_cast<int>(type) * halfSquareSize, 0, halfSquareSize, halfSquareSize));
	this->cells = tetrominos[static_cast<int>(type)];
}

Tetromino::Tetromino(Type type, bool isGhost) : Tetromino(type)
{
	if (isGhost)
		cellImage.setColor(sf::Color(255, 255, 255, 100));
}

Tetromino::~Tetromino()
{
}

Tetromino Tetromino::getGhost(Board& board)
{
	Tetromino ghost = *this;
	ghost.turnToGhostColor();
	while (ghost.move(Moving_Direction::DOWN_DIR, board));
	return ghost;
}

void Tetromino::turnToGhostColor()
{
	cellImage.setColor(sf::Color(255, 255, 255, 50));
}

// moving direction is the mouse direction in this method
bool Tetromino::setPiece(int x, int y, Moving_Direction mDir, Board& board)
{
	using namespace std;
	Orientation newOrientation = orientationFromMouse[static_cast<int>(type)][static_cast<int>(mDir)];
	Rotational_Direction rDir = static_cast<Rotational_Direction> ((static_cast<int>(newOrientation) - static_cast<int> (orientation) + 5) % 4 - 1);
	array<array<int, 4>, 4> tempCells = cells;

	switch (type)
	{
	case Type::I:
		rotateArray(cells, 4, rDir);
		break;
	case Type::O:
		break;
	default: // T, L, J, Z,S
		rotateArray(cells, 3, rDir);
		break;
	}

	int shiftPosX = shiftPos[static_cast<int>(type)][static_cast<int>(newOrientation)][0];
	int shiftPosY = shiftPos[static_cast<int>(type)][static_cast<int>(newOrientation)][1];
	bool possible = checkCollision(x + shiftPosX, y + shiftPosY, board);
	x = x + shiftPosX;
	y = y + shiftPosY;
	std::cout << "x:" << x << "\t" << y<< std::endl;

	if (possible)
	{
		this->xPos = x;
		this->yPos = y;
		orientation = newOrientation;
		hardDrop(board);
	}
	else // not possible. discard
	{
		cells = tempCells;
	}


	return possible;
}



bool Tetromino::rotate(Rotational_Direction rDir, Board& board)
{
	using namespace std;
	int newOrientationInt = ((static_cast<int>(orientation) + static_cast<int>(rDir)) + 4) % 4;
	Orientation newOrientation = static_cast<Orientation> (newOrientationInt);
	int wallKickGroup = 0;
	array<array<int, 4>, 4> tempCells = cells;


	switch (type)
	{
	case Type::I:
		cells = tetrominos[static_cast<int>(type)];
		if (newOrientation == Orientation::RIGHT || newOrientation == Orientation::LEFT)
		{
			rotateArray(cells, 4, Rotational_Direction::CCW);
		}
		break;
	case Type::O:
		break;
	case Type::Z:
	case Type::S:
		cells = tetrominos[static_cast<int>(type)];
		if (newOrientation == Orientation::RIGHT || newOrientation == Orientation::LEFT)
		{
			rotateArray(cells, 3, Rotational_Direction::CCW);
		}
		break;
	default: // T, L, J, Z,S
		rotateArray(cells, 3, rDir);
		break;
	}


	// TODO: check collision here, wall kick
		//cout << xOffset << ',' << yOffset << endl;
		// yOffset is negate cuz positve y means upwards while in our board array positve y moves downward

	std::array<int, 3> move = firstPossibleMoveNoRo(board);
	// if no possible move, reset to original orientation
	if (move[2] == 0)
	{
		cells = tempCells;
		return false;
	}
	orientation = newOrientation;
	return true;
}


int Tetromino::hardDrop(Board& board)
{
	int cellsDropped = 0;
	while (move(Moving_Direction::DOWN_DIR, board))
	{
		cellsDropped++;
	}
	setPiece(board);
	return cellsDropped;
}

void Tetromino::setPiece(Board& board)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] == 0) continue;
			board.setCell(i + yPos, j + xPos, cells[i][j]);
		}
	}
}

bool Tetromino::checkIsOnGround(Board& board)
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				//cout << xPos + j << ',' << yPos + i + 1<<endl;
				if (yPos + i + 1 >= boardHeight || board.getCell(yPos + i + 1, xPos + j) > 0)
				{
					isOnGround = true;
					return isOnGround;
				}
			}
		}
	}

	isOnGround = false;
	return isOnGround;
}

// Rotate a square array
// TODO: Check rotation is correct
void Tetromino::rotateArray(std::array<std::array<int, 4>, 4>& arr, int size, Rotational_Direction rDir)
{
	using namespace std;
	// TODO: Check this copy
	array<array<int, 4>, 4> temp;
	temp = arr;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (rDir == Rotational_Direction::CW)
				arr[j][size - i - 1] = temp[i][j];
			else if (rDir == Rotational_Direction::CCW)
				arr[size - j - 1][i] = temp[i][j];
			else if (rDir == Rotational_Direction::R180)
				arr[i][j] = temp[size - i - 1][size - j - 1];
		}
	}
}

bool Tetromino::move(Moving_Direction dir, Board& board)
{
	int newXPos = xPos;
	int newYPos = yPos;
	if (dir == Moving_Direction::RIGHT_DIR)
	{
		newXPos++;
	}
	else if (dir == Moving_Direction::LEFT_DIR)
	{
		newXPos--;
	}
	else if (dir == Moving_Direction::DOWN_DIR)
	{
		newYPos++;
	}
	else if (dir == Moving_Direction::UP_DIR)
	{
		newYPos--;
	}
	bool isPossible = setXY(newXPos, newYPos, board);
	if (isPossible) rotateLast = false;
	checkIsOnGround(board);
	return isPossible;
}

bool Tetromino::checkCollision(int xPos, int yPos, Board& board)
{
	using namespace std;
	array<array<short, boardWidth>, boardHeight> boardMatrix = board.getBoard();
	//Traverse the cells if it collide with any blocks on the board
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// if there is no cells here, skip
			if (cells[i][j] <= 0) continue;

			// else if that location on board hit the wall or a non-empty block => not valid move
			if (xPos + j < 0 || xPos + j >= boardWidth || yPos + i >= boardHeight || yPos + i < 0 || boardMatrix[yPos + i][xPos + j] > 0)
			{
				//cout << xPos + j << ',' << yPos + i << endl;
				return false;
			}
		}
	}
	return true;
}

bool Tetromino::checkCollision(Board& board)
{
	using namespace std;
	array<array<short, boardWidth>, boardHeight> boardMatrix = board.getBoard();
	//Traverse the cells if it collide with any blocks on the board
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// if there is no cells here, skip
			if (cells[i][j] <= 0) continue;

			// else if that location on board hit the wall or a non-empty block => not valid move
			if (xPos + j < 0 || xPos + j >= boardWidth || yPos + i >= boardHeight || yPos + i < 0 || boardMatrix[yPos + i][xPos + j] > 0)
			{
				//cout << xPos + j << ',' << yPos + i << endl;
				return false;
			}
		}
	}
	return true;
}

std::array<int, 3> Tetromino::firstPossibleMoveNoRo(Board& board)
{
	//Traverse the cells if it collide with any blocks on the board
	for (int i = -getMinX(); i <= 9 - getMaxX(); i++)
	{
		for (int j = -getMinY(); j <= 9 - getMaxY(); j++)
		{
			if (checkCollision(i, j, board))return { i,j,1 };
		}
	}
	return { -1,-1,0 };
}

std::array<int, 4> Tetromino::firstPossibleMove(Board& board)
{
	Tetromino temp = *this;
	bool valid = false;
	for (int o = 0; o < 4; o++)
	{
		temp.reset();
		switch (o)
		{
		case 0:
			valid = temp.rotate(Rotational_Direction::NORO, board);
			break;
		case 1:
			valid = temp.rotate(Rotational_Direction::CW, board);
			break;
		case 2:
			valid = temp.rotate(Rotational_Direction::R180, board);
			break;
		case 3:
			valid = temp.rotate(Rotational_Direction::CCW, board);
			break;
		default:
			break;
		};
		if (valid)
		{
			std::array<int, 3> res = temp.firstPossibleMoveNoRo(board);
			return { res[0], res[1],o, 1 };
		}
	}
	return { -1,-1,-1,0 };
}

void Tetromino::render(sf::RenderWindow& window, Board& board)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				cellImage.setPosition(board.getXPos() + (xPos + j) * boardSquareSize, board.getYPos() + (yPos + i) * boardSquareSize);
				cellImage.setScale(sf::Vector2f(2, 2));
				window.draw(cellImage);
			}
		}
	}
}

void Tetromino::render(sf::RenderWindow& window, int x, int y, int scale)
{
	int blockSize = squareSize * (float)scale / 2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				cellImage.setPosition(x + j * blockSize, y + i * blockSize);
				cellImage.setScale(sf::Vector2f(scale, scale));
				window.draw(cellImage);
			}
		}
	}
}

void Tetromino::setTransparency(sf::Uint8 transparency)
{
	cellImage.setColor(sf::Color(255, 255, 255, transparency));
}

void Tetromino::renderBorder(sf::RenderWindow& window, Board& board, sf::Color color)
{
	using namespace sf;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				RectangleShape rect(Vector2f(squareSize - 10, squareSize - 10));
				rect.setFillColor(Color(255, 255, 255, 50));
				rect.setOutlineColor(color);
				rect.setOutlineThickness(10);
				rect.setPosition(board.getXPos() + (xPos + j) * squareSize + 5, board.getYPos() + (yPos + i) * squareSize + 5);
				window.draw(rect);
			}
		}
	}
}

void Tetromino::reset()
{
	xPos = 3;
	yPos = 1;
	orientation = Orientation::SPAWN;
	cells = tetrominos[static_cast<int>(type)];
	isOnGround = false;

}

Type Tetromino::getType()
{
	return type;
}

int Tetromino::getXPos()
{
	return xPos;
}

int Tetromino::getYPos()
{
	return yPos;
}

Orientation Tetromino::getOrientation()
{
	return orientation;
}

bool Tetromino::getRotateLast()
{
	return rotateLast;
}

bool Tetromino::setXY(int xPos, int yPos, Board& board)
{
	bool possible = checkCollision(xPos, yPos, board);

	if (possible)
	{
		this->xPos = xPos;
		this->yPos = yPos;
	}
	return possible;
}

void Tetromino::setXY(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}


//bool Tetromino::setXY(int xPos, int yPos, Rotational_Direction rDir)
//{
//	bool possible = checkCollision(xPos, yPos, rDir);
//	if (possible)
//	{
//		this->xPos = xPos;
//		this->yPos = yPos;
//	}
//	return possible;
//}


int Tetromino::getMinX()
{
	if (cells[0][0] != 0 || cells[1][0] != 0 || cells[2][0] != 0)
	{
		return 0;
	}
	else if (cells[1][1] != 0)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int Tetromino::getMinY()
{
	if (cells[0][0] != 0 || cells[0][1] != 0 || cells[0][2] != 0)
	{
		return 0;
	}
	else if (cells[1][1] != 0)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int Tetromino::getMaxX()
{
	if (cells[0][3] != 0 || cells[1][3] != 0)
	{
		return 3;
	}
	else if (cells[0][2] != 0 || cells[1][2] != 0 || cells[2][2] != 0)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int Tetromino::getMaxY()
{
	if (cells[3][1] != 0 || cells[3][2] != 0)
	{
		return 3;
	}
	else if (cells[2][0] != 0 || cells[2][1] != 0 || cells[2][2] != 0)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int Tetromino::getSquareCountX()
{
	return getMaxX() - getMinX() + 1;
}

int Tetromino::getSquareCountY()
{
	return getMaxY() - getMinY() + 1;
}

