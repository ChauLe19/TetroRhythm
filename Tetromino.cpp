#include "Tetromino.h"

Tetromino::Tetromino(Type type)
{
	this->type = type;
	cellsTexture.loadFromFile("tiles.png");
	cellImage.setTexture(cellsTexture);
	cellImage.setTextureRect(IntRect(static_cast<int>(type) * 18, 0, 18, 18));
	// TODO: Check if this copied
	this->cells = tetrominos[static_cast<int>(type)];
}

Tetromino::~Tetromino()
{
	delete& cells;
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
		return true;
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
		cout << xOffset << ',' << yOffset << endl;
		// yOffset is negate cuz positve y means upwards while in our board array positve y moves downward
		if (checkCollision(xPos + xOffset, yPos - yOffset, tempCells, board))
		{
			cout << "working:" << xOffset << ',' << yOffset << endl;
			xPos += xOffset;
			yPos -= yOffset;
			cells = tempCells;
			orientation = newOrientation;
			return true;
		}
	}

	return false;
}


void Tetromino::hardDrop(Board& board)
{
	while (move(Moving_Direction::DOWN_DIR, board));
	setPiece(board);
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
	return setXY(newXPos, newYPos, board);
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
			if (xPos + j < 0 || xPos + j >= boardWidth || yPos + i >= boardHeight || boardMatrix[yPos + i][xPos + j] > 0)
			{
				//cout << xPos + j << ',' << yPos + i << endl;
				return false;
			}
		}
	}
	return true;
}

void Tetromino::render(RenderWindow& window, Board& board)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cells[i][j] > 0)
			{
				cellImage.setPosition(board.getXPos() + (xPos + j) * 18, board.getYPos() + (yPos + i) * 18);
				window.draw(cellImage);
			}
		}
	}
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
