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

enum class ClearType {
	NONE,
	SINGLE,
	DOUBLE,
	TRIPLE,
	TETRIS,  // standard
	TSPIN_MINI_NO,
	TSPIN_NO,
	TSPIN_MINI_SINGLE,
	TSPIN_SINGLE,
	TSPIN_MINI_DOUBLE,
	TSPIN_DOUBLE,
	TSPIN_TRIPLE, // t-spin
	COMBO,
	SOFTDROP,
	HARDDROP, // others
	SINGLE_LINE_PC,
	DOUBLE_LINE_PC,
	TRIPLE_LINE_PC,
	TETRIS_PC,
	B2B_TETRIS_PC, // pc
	B2B_TETRIS,  // standard
	B2B_TSPIN_MINI_SINGLE,
	B2B_TSPIN_SINGLE,
	B2B_TSPIN_MINI_DOUBLE,
	B2B_TSPIN_DOUBLE,
	B2B_TSPIN_TRIPLE, // t-spin
};

static int clearTypeScore[] = { 0,
100,
300,
500,
800,
100,
400,
200,
800,
400,
1200,
1600,
50,
1,
2,
800,
1200,
1800,
2000,
3200,
1200,
300,
1200,
600,
1800,
2400
};

struct ClearingInfo
{
	int linesCleared;
	bool isPC;
};

class Board
{
private:
	array<array<int, boardWidth>, boardHeight> board = { 0 };
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
	ClearingInfo clearLines();
	ClearingInfo clearLines(ClearType prevType);
	array<array<int, boardWidth>, boardHeight> getBoard();
	int getXPos();
	int getYPos();
	void setCell(int x, int y, int value);
	int getCell(int x, int y);
	void print();
};
#endif

