#include "Board.h"
Board::Board(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
	frameTexture.loadFromFile("Images/frame flat.png");
	image.setTexture(frameTexture);
	image.setPosition((float)xPos - 255, (float)yPos - 10);
	cellsTexture.loadFromFile("Images/tiles-2.png");
	cellImage.setTexture(cellsTexture);

}

Board::Board()
{
	frameTexture.loadFromFile("Images/frame-white.png");
	image.setTexture(frameTexture);
	image.setPosition((float)0, (float)0);
	cellsTexture.loadFromFile("Images/tiles-2.png");
	cellImage.setTexture(cellsTexture);
}

Board::~Board()
{
}

void Board::render(RenderWindow& window)
{


	/*window.draw(image);
	RectangleShape rect(Vector2f(squareSize * 10, squareSize * 20));
	rect.setFillColor(Color(0, 0, 0, 150));
	rect.setPosition(xPos, yPos);
	rect.setOutlineColor(Color::White);
	rect.setOutlineThickness(5);*/
	//rect.setFillColor(Color(25,25,25,255));
	//rect.setFillColor(Color::White);
	//window.draw(rect);
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			RectangleShape rect(Vector2f(squareSize, squareSize));
			rect.setFillColor(Color(0, 0, 0, 150));
			rect.setPosition(xPos + squareSize * j, yPos + squareSize * i);
			rect.setOutlineColor(Color(255, 255, 255, 100));
			rect.setOutlineThickness(5);
			window.draw(rect);
			if (board[i][j] % 8 != 0)
			{
				cellImage.setTextureRect(IntRect((board[i][j] % 8 - 1) * 45, 0, 45, 45));
				cellImage.setScale(Vector2f(2, 2));
				cellImage.setPosition(xPos + squareSize * j, yPos + squareSize * i);
				window.draw(cellImage);
			}

		}
	}
}


ClearingInfo Board::clearLines()
{
	array<array<int, boardWidth>, boardHeight> tempBoard = board;
	int linesCleared = 0;
	bool isPC = true;

	for (int i = 0; i < boardHeight; i++)
	{
		bool horizontalLineIsFilled = true;
		bool linePC = true;
		// check if line is filled
		for (int j = 0; j < boardWidth; j++)
		{
			if (tempBoard[i][j] == 0)
			{
				horizontalLineIsFilled = false;
			}

			// in a line, if tiles switch from filled and empty -> not clearing -> not pc
			if (j != 0 && tempBoard[i][j] != tempBoard[i][j - 1] && (tempBoard[i][j] == 0 || tempBoard[i][j - 1] == 0))
			{
				isPC = false;
				break;
			}
		}
		// if line is filled, clear
		if (horizontalLineIsFilled)
		{
			linesCleared++;
			for (int j = 0; j < boardWidth; j++)
			{
				board[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < boardWidth; j++)
	{
		bool verticalLineIsFilled = true;
		bool linePC = true;
		// check if line is filled
		for (int i = 0; i < boardHeight; i++)
		{
			if (tempBoard[i][j] == 0)
			{
				verticalLineIsFilled = false;
			}

			// in a line, if tiles switch from filled and empty -> not clearing -> not pc
			if (i != 0 && tempBoard[i][j] != tempBoard[i - 1][j] && (tempBoard[i][j] == 0 || tempBoard[i - 1][j] == 0))
			{
				isPC = false;
				break;
			}
		}
		// if line is filled, clear
		if (verticalLineIsFilled)
		{
			linesCleared++;
			for (int k = 0; k < boardHeight; k++)
			{
				board[k][j] = 0;
			}
		}
	}

	struct ClearingInfo result;
	result.isPC = isPC;
	result.linesCleared = linesCleared;
	return result;
}



// TODO: check if this return a copy or reference
array<array<int, boardWidth>, boardHeight> Board::getBoard()
{
	return board;
}

void Board::setCell(int x, int y, int value)
{
	board[x][y] = value;
}

int Board::getCell(int x, int y)
{
	return board[x][y];
}

bool Board::createGarbageLine(int holePos)
{
	// move up the board
	for (int i = 0; i < boardHeight - 1; i++)
	{
		for (int k = 0; k < boardWidth; k++)
		{
			// if the top has block, can't create a garbage line
			if (i == 0 && board[i][k] != 0)
			{
				return false;
			}
			else if (i == 0)
			{
				continue;
			}

			board[i][k] = board[i + 1][k];
		}
	}

	// create garbage line
	for (int k = 0; k < boardWidth; k++)
	{
		if (k == holePos)
		{
			board[boardHeight - 1][k] = 0;
		}
		else
		{
			board[boardHeight - 1][k] = 8;
		}
	}
	return true;
}

void Board::print()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}

int Board::getXPos()
{
	return xPos;
}

int Board::getYPos()
{
	return yPos;
}

