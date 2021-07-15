#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
#define boardWidth 10
#define boardHeight 20
//#define matrixWidth boardWidth + 2
//#define matrixHeight boardHeight + 2

class Board
{
private:
	array<array<int, boardWidth>, boardHeight> board = {0};
	int xPos = 0;
	int yPos = 0;
	Texture frameTexture;
	Texture cellsTexture;
	Sprite image;
	Sprite cellImage;
public:
	Board();
	Board(int xPos, int yPos);
	~Board();
	void render(RenderWindow& window);
	Sprite& sprite();
	void clearLines();
	array<array<int, boardWidth>, boardHeight> getBoard();
	int getXPos();
	int getYPos();
	void setCell(int x, int y, int value);
	int getCell(int x, int y);
};
#endif

