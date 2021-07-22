#include "Board.h"
Board::Board(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
	frameTexture.loadFromFile("Images/frame-white.png");
	image.setTexture(frameTexture);
	image.setPosition((float)xPos-70, (float)yPos);
	cellsTexture.loadFromFile("Images/tiles-dark-2-full-mid.png");
	cellImage.setTexture(cellsTexture);

}

Board::Board()
{
	frameTexture.loadFromFile("Images/frame-white.png");
	image.setTexture(frameTexture);
	image.setPosition((float)0, (float)0);
	cellsTexture.loadFromFile("Images/tiles-dark-2-full-mid.png");
	cellImage.setTexture(cellsTexture);
}
Board::~Board()
{
}
void Board::render(RenderWindow& window)
{
	window.draw(image);
	//RectangleShape rect(Vector2f(18 * 10, 18 * 20));
	/*rect.setFillColor(Color(200,200,200,255));
	rect.setPosition(xPos, yPos);*/

	//rect.setFillColor(Color(25,25,25,255));
	//rect.setFillColor(Color::White);
	//window.draw(rect);
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
			for (int k = i; k > 0; k--)
			{
				for (int j = 0; j < boardWidth; j++)
				{
					board[k][j] = board[k - 1][j];
				}
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

