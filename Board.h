/*****************************************************************//**
 * \file   Board.h
 * \brief  Board representation
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/

#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define boardWidth 6
#define boardHeight 6
#define boardSquareSize 135 // px
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
	B2B_PENTRIS_PC,
	B2B_PENTRIS,
	PENTRIS_PC,
	PENTRIS
};

// Scoring array mapping with the ClearType enums
static int clearTypeScore[] = { 0,
100,
300,
500,
800,
0,
0,
200,
800,
400,
1200,
1600,
0,
0,
0,
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
2400,
5000,
3000,
3000,
2400
};

struct ClearingInfo
{
	int linesCleared;
	bool isPC;
};


/**
 * Controls the board.
 */
class Board
{
private:
	Sprite image;
	Sprite cellImage;

	array<array<short, boardWidth>, boardHeight> board = { 0 };
	int xPos = 0;
	int yPos = 0;

public:
	Board();
	Board(int xPos, int yPos);
	~Board();

	/**
	 * Draw board.
	 */
	void render(RenderWindow& window);

	/**
	 * Clear all lines that werre filled.
	 *
	 * \return Clearing info of how many lines was cleared and if it results a pc
	 */
	ClearingInfo clearLines();

	bool createGarbageLine(int holePos);


	/**
	 * Get an array representation of the board.
	 */
	array<array<short, boardWidth>, boardHeight> getBoard();

	/**
	 * Set cell with a specific value.
	 * \param x Row index
	 * \param y Column index
	 * \param value Value to be assigned at x and y position
	 */
	void setCell(int x, int y, int value);

	/**
	 * Get cell's value.
	 *
	 * \param x Row index
	 * \param y Column index
	 * \return cell's valuea at x any y position in array
	 */
	int getCell(int x, int y);

	/**
	 * Print out array representation of board in the console.
	 */
	void print();


	void setBoard(std::array<std::array<short, boardHeight>, boardWidth> board);

	void clearBoard();
	void enforceGravity();

	int getXPos();
	int getYPos();
};
#endif

