#include "Tetromino.h"

Tetromino::Tetromino(Type type)
{
	this->type = type;
	cellsTexture.loadFromFile("Images/tiles-2.png");
	cellImage.setTexture(cellsTexture);
	cellImage.setTextureRect(IntRect(static_cast<int>(type) * 45, 0, 45, 45));
	// TODO: Check if this copied
	this->cells = tetrominos[static_cast<int>(type)];
	// center always [1,1]
	switch (type)
	{
	case Type::I: // can be in spawn state or state after CCW
		rotateArray(this->cells, 4, static_cast<Rotational_Direction>((std::rand() % 2) - 1));
		break;
	case Type::S: // can be in spawn state or state after CW
	case Type::Z:
		rotateArray(this->cells, 3, static_cast<Rotational_Direction>(std::rand() % 2));
		break;
	case Type::O: // only 1 state
		break;
	default: // T, L, J
		rotateArray(this->cells, 3, static_cast<Rotational_Direction>((std::rand() % 4) - 1));
		break;
	}
}

Tetromino::Tetromino(Type type, bool isGhost)
{
	this->type = type;
	cellsTexture.loadFromFile("Images/tiles-2.png");
	cellImage.setTexture(cellsTexture);
	if (isGhost)
		cellImage.setColor(Color(255, 255, 255, 100));
	cellImage.setTextureRect(IntRect(static_cast<int>(type) * 45, 0, 45, 45));
	// TODO: Check if this copied
	this->cells = tetrominos[static_cast<int>(type)];

}

Tetromino::~Tetromino()
{
}

Tetromino Tetromino::getGhost(Board& board)
{
	Tetromino ghost = *this;
	ghost.turnToGhostColor();
	//while (ghost.move(Moving_Direction::DOWN_DIR, board));
	return ghost;
}

void Tetromino::turnToGhostColor()
{
	cellImage.setColor(Color(255, 255, 255, 50));
}

bool Tetromino::rotate(Rotational_Direction rDir, Board& board)
{
	if (rDir == Rotational_Direction::NORO) return true;
	int newOrientationInt = ((static_cast<int>(orientation) + static_cast<int>(rDir)) + 4) % 4;
	Orientation newOrientation = static_cast<Orientation> (newOrientationInt);
	array<array<array<int, 2>, 5>, 8>* wallKickDataPtr = new array<array<array<int, 2>, 5>, 8>();
	array<array<array<int, 2>, 5>, 8> wallKickData = *wallKickDataPtr;
	int wallKickGroup = 0;
	// might not be copy
	// TODO: check if this copied
	array<array<int, 4>, 4> tempCells;
	tempCells = cells;


	switch (type)
	{
	case Type::I:
		rotateArray(tempCells, 4, rDir);
		wallKickData = IWallKickData;
		break;
	case Type::O:
		// if rotate CW, can't move to the bottom right corner, do O-spin if possible 
		if (rDir == Rotational_Direction::CW && !checkCollision(xPos + 1, yPos + 1, cells, board))
		{
			if (checkCollision(xPos + 2, yPos + 2, cells, board))
			{
				cout << "CW O spin" << endl;
				xPos += 2;
				yPos += 2;
				orientation = newOrientation;
				rotateLast = true;
				return true;
			}
			return false;
		}
		// if rotate CCW, can't move to the bottom left corner, do O-spin if possible 
		else if (rDir == Rotational_Direction::CCW && !checkCollision(xPos - 1, yPos + 1, cells, board))
		{
			if (checkCollision(xPos - 2, yPos + 2, cells, board))
			{
				cout << "CCW O spin" << endl;
				xPos -= 2;
				yPos += 2;
				orientation = newOrientation;
				rotateLast = true;
				return true;
			}
			return false;
		}
		return false;
		break;
	default: // T, L, J, Z,S
		rotateArray(tempCells, 3, rDir);
		wallKickData = JLSTZWallKickData;
		break;
	}

	if (orientation == Orientation::SPAWN && newOrientation == Orientation::RIGHT)
	{
		wallKickGroup = 0;
	}
	else if (orientation == Orientation::RIGHT && newOrientation == Orientation::SPAWN)
	{
		wallKickGroup = 1;
	}
	else if (orientation == Orientation::RIGHT && newOrientation == Orientation::FLIP)
	{
		wallKickGroup = 2;
	}
	else if (orientation == Orientation::FLIP && newOrientation == Orientation::RIGHT)
	{
		wallKickGroup = 3;
	}
	else if (orientation == Orientation::FLIP && newOrientation == Orientation::LEFT)
	{
		wallKickGroup = 4;
	}
	else if (orientation == Orientation::LEFT && newOrientation == Orientation::FLIP)
	{
		wallKickGroup = 5;
	}
	else if (orientation == Orientation::LEFT && newOrientation == Orientation::SPAWN)
	{
		wallKickGroup = 6;
	}
	else if (orientation == Orientation::SPAWN && newOrientation == Orientation::LEFT)
	{
		wallKickGroup = 7;
	}

	// TODO: check collision here, wall kick
	for (int i = 0; i < 5; i++)
	{
		int xOffset = wallKickData[wallKickGroup][i][0];
		int yOffset = wallKickData[wallKickGroup][i][1];
		//cout << xOffset << ',' << yOffset << endl;
		// yOffset is negate cuz positve y means upwards while in our board array positve y moves downward
		if (checkCollision(xPos + xOffset, yPos - yOffset, tempCells, board))
		{
			//cout << "working:" << xOffset << ',' << yOffset << endl;
			xPos += xOffset;
			yPos -= yOffset;
			cells = tempCells;
			orientation = newOrientation;
			rotateLast = true;
			return true;
		}
	}

	return false;
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
void Tetromino::rotateArray(array<array<int, 4>, 4>& arr, int size, Rotational_Direction rDir)
{
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

bool Tetromino::checkCollision(int xPos, int yPos, array<array<int, 4>, 4> cells, Board& board)
{
	array<array<int, boardWidth>, boardHeight> boardMatrix = board.getBoard();
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
	array<array<int, boardWidth>, boardHeight> boardMatrix = board.getBoard();
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

std::array<int, 3> Tetromino::firstPossibleMove(Board& board)
{
	array<array<int, boardWidth>, boardHeight> boardMatrix = board.getBoard();
	//Traverse the cells if it collide with any blocks on the board
	for (int i = -getMinX(); i <= 9 - getMaxX(); i++)
	{
		for (int j = -getMinY(); j <= 9 - getMaxY(); j++)
		{
			if (checkCollision(i, j, cells, board))return { i,j,1 };
		}
	}
	return { -1,-1,0 };
}

void Tetromino::render(RenderWindow& window, Board& board)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				cellImage.setPosition(board.getXPos() + (xPos + j) * squareSize, board.getYPos() + (yPos + i) * squareSize);
				cellImage.setScale(Vector2f(2, 2));
				window.draw(cellImage);
			}
		}
	}
}


void Tetromino::setTransparency(sf::Uint8 transparency)
{
	cellImage.setColor(Color(255, 255, 255, transparency));
}

void Tetromino::renderBorder(RenderWindow& window, Board& board, Color color)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				RectangleShape rect(Vector2f(squareSize - 10, squareSize - 10));
				rect.setFillColor(Color(255,255,255,50));
				rect.setOutlineColor(color);
				rect.setOutlineThickness(10);
				rect.setPosition(board.getXPos() + (xPos + j) * squareSize + 5, board.getYPos() + (yPos + i) * squareSize + 5);
				window.draw(rect);
			}
		}
	}
}

void Tetromino::render(RenderWindow& window, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				cellImage.setPosition(x + j * squareSize, y + i * squareSize);
				cellImage.setScale(Vector2f(2, 2));
				window.draw(cellImage);
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
	bool possible = checkCollision(xPos, yPos, this->cells, board);

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

