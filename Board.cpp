#include "Board.h"
Board::Board(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
	frameTexture.loadFromFile("Images/frame.png");
	image.setTexture(frameTexture);
	image.setScale(4, 4);
	image.setPosition((float)xPos, (float)yPos);
	cellsTexture.loadFromFile("Images/tiles-2.png");
	cellImage.setTexture(cellsTexture);

}

Board::Board()
{
	frameTexture.loadFromFile("Images/frame flat.png");
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
	RectangleShape frame(Vector2f(boardSquareSize * boardWidth, boardSquareSize * boardHeight));
	frame.setOutlineThickness(10);
	frame.setOutlineColor(Color(63,119,179));
	frame.setPosition(xPos, yPos);
	frame.setFillColor(Color::Transparent);
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			RectangleShape rect(Vector2f(boardSquareSize, boardSquareSize));
			rect.setFillColor(Color(0, 0, 0, 150));
			rect.setPosition(xPos + boardSquareSize * j, yPos + boardSquareSize * i);
			rect.setOutlineColor(Color(0, 168, 236, 50));
			rect.setOutlineThickness(5);
			window.draw(rect);
			if (board[i][j] % 8 != 0)
			{
				cellImage.setTextureRect(IntRect((board[i][j] % 8 - 1) * 45, 0, 45, 45));
				cellImage.setScale(Vector2f(3, 3));
				cellImage.setPosition(xPos + boardSquareSize * j, yPos + boardSquareSize * i);
				window.draw(cellImage);
			}

		}
	}
	window.draw(frame);
}


ClearingInfo Board::clearLines()
{
	int linesCleared = 0;
	bool isPC = true;

	for (int i = 0; i < boardHeight; i++)
	{
		bool lineIsFilled = true;
		bool linePC = true;
		// check if line is filled
		for (int j = 0; j < boardWidth; j++)
		{
			if (board[i][j] == 0)
			{
				lineIsFilled = false;
			}

			// in a line, if tiles switch from filled and empty -> not clearing -> not pc
			if (j != 0 && board[i][j] != board[i][j - 1] && (board[i][j] == 0 || board[i][j - 1] == 0))
			{
				isPC = false;
				break;
			}
		}
		// if line is filled, clear
		if (lineIsFilled)
		{
			linesCleared++;
			for (int k = i; k >= 0; k--)
			{
				for (int j = 0; j < boardWidth; j++)
				{
					if (k == 0)
					{
						board[k][j] = 0;
					}
					else
					{
						board[k][j] = board[k - 1][j];
					}
				}
			}
		}
	}
	struct ClearingInfo result;
	result.isPC = isPC;
	result.linesCleared = linesCleared;
	return result;

}

void Board::clearBoard()
{
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			board[i][j] = 0;
		}
	}
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

