#include "Board.h"
Board::Board(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
	frameTexture.loadFromFile("frame.png");
	image.setTexture(frameTexture);
	image.setPosition((float)xPos, (float)yPos);
	cellsTexture.loadFromFile("tiles.png");
	cellImage.setTexture(cellsTexture);

}

Board::Board()
{
	frameTexture.loadFromFile("frame.png");
	image.setTexture(frameTexture);
	image.setPosition((float) 0, (float)0);
	cellsTexture.loadFromFile("tiles.png");
	cellImage.setTexture(cellsTexture);
}
Board::~Board()
{
}
void Board::render(RenderWindow& window)
{

	RectangleShape rect(Vector2f(18 * 10, 18 * 20));
	rect.setFillColor(Color::Green);
	rect.setPosition(xPos, yPos);
	window.draw(rect);
	// Doesn't render the first line
	for (int i = 1; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (board[i][j] > 0)
			{
				cellImage.setTextureRect(IntRect((board[i][j] - 1) * 18, 0, 18, 18));
				cellImage.setPosition(xPos + 18 * j, yPos + 18 * i);
				window.draw(cellImage);
			}
		}
	}
}

void Board::clearLines()
{
	int linesCleared = 0;
	bool pc = true;

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
				break;
			}
		}

		// if line is filled, clear
		linesCleared++;
		if (lineIsFilled)
		{
			for (int k = i; k > 0; k--)
			{
				for (int j = 0; j < boardWidth; j++)
				{
					board[k][j] = board[k - 1][j];
				}
			}
		}
	}

}

// TODO: check if this return a copy or reference
array<array<int, boardWidth>, boardHeight> Board::getBoard()
{
	return board;
}

int Board::getXPos()
{
	return xPos;
}
int Board::getYPos()
{
	return yPos;
}

void Board::setCell(int x, int y, int value)
{
	board[x][y] = value;
}

int Board::getCell(int x, int y)
{
	return board[x][y];
}

