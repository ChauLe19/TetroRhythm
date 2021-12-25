/*****************************************************************//**
 * \file   Tetromino.h
 * \brief  Tetromino representation. Rotate, move, etc...
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Board.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>

using namespace std;

enum class Type { Z = 0, L = 1, O = 2, S = 3, I = 4, J = 5, T = 6 };
enum class Orientation { SPAWN = 0, RIGHT = 1, FLIP = 2, LEFT = 3 };
enum class Rotational_Direction { CCW = -1, NORO = 0, CW = 1, R180 = 2 };
enum class Moving_Direction { UP_DIR = 0, LEFT_DIR = 1, RIGHT_DIR = 2, DOWN_DIR = 3 };
const static vector<Type> allPieces{ Type::Z, Type::L, Type::O, Type::S, Type::I,Type::J,Type::T };



const static std::array<std::array<std::array<int, 4>, 4>, 7> tetrominos = { {
											{{  //Z block
												{1, 1, 0, 0},
												{0, 1, 1, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //L block
												{0, 0, 2, 0},
												{2, 2, 2, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //O block
												{0, 3, 3, 0},
												{0, 3, 3, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //S block
												{0, 4, 4, 0},
												{4, 4, 0, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //I block
												{0, 0, 0, 0},
												{5, 5, 5, 5},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //J block
												{6, 0, 0, 0},
												{6, 6, 6, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //T block
												{0, 7, 0, 0},
												{7, 7, 7, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
										} };


// 0 = spawn state
// R = state resulting from a clockwise rotation("right") from spawn
// L = state resulting from a counter - clockwise("left") rotation from spawn
// 2 = state resulting from 2 successive rotations in either direction from spawn.

const static std::array<std::array<std::array<int, 2>, 5>, 8> JLSTZWallKickData = { {
													{{ // 0 -> R
														{0,0}, {-1,0}, {-1, 1}, {0,-2}, {-1,-2}
													}},
													{{ // R -> 0
														{0,0}, { 1,0}, { 1,-1}, {0, 2}, { 1, 2}
													}},
													{{ // R -> 2
														{0,0}, { 1,0}, { 1,-1}, {0, 2}, { 1, 2}
													}},
													{{ // 2 -> R
														{0,0}, {-1,0}, {-1, 1}, {0,-2}, {-1,-2}
													}},
													{{ // 2 -> L
														{0,0}, { 1,0}, { 1, 1}, {0,-2}, { 1,-2}
													}},
													{{ // L -> 2
														{0,0}, {-1,0}, {-1,-1}, {0, 2}, {-1, 2}
													}},
													{{ // L -> 0
														{0,0}, {-1,0}, {-1,-1}, {0, 2}, {-1, 2}
													}},
													{{ // 0 -> L
														{0,0}, { 1,0}, { 1, 1}, {0,-2}, { 1,-2}
													}},
} };

const static std::array<std::array<std::array<int, 2>, 5>, 8> IWallKickData = { {
												{{ // 0 -> R
													{0,0}, {-2,0}, { 1, 0}, {-2,-1}, { 1, 2}
												}},
												{{ // R -> 0
													{0,0}, { 2,0}, {-1, 0}, { 2, 1}, {-1,-2}
												}},
												{{ // R -> 2
													{0,0}, {-1,0}, { 2, 0}, {-1, 2}, { 2,-1}
												}},
												{{ // 2 -> R
													{0,0}, { 1,0}, {-2, 0}, { 1,-2}, {-2, 1}
												}},
												{{ // 2 -> L
													{0,0}, { 2,0}, {-1, 0}, { 2, 1}, {-1,-2}
												}},
												{{ // L -> 2
													{0,0}, {-2,0}, { 1, 0}, {-2,-1}, { 1, 2}
												}},
												{{ // L -> 0
													{0,0}, { 1,0}, {-2, 0}, { 1,-2}, {-2, 1}
												}},
												{{ // 0 -> L
													{0,0}, {-1,0}, { 2, 0}, {-1, 2}, { 2,-1}
												}},
} };



/**
 * Tetromino representation.
 */
class Tetromino
{
private:
	static const int squareSize = 90;
	Texture cellsTexture;
	Sprite cellImage;
	Orientation orientation = Orientation::SPAWN;

	array<array<int, 4>, 4> cells = { 0 };
	Type type;

	// Spawn position
	//*****************************************

	int xPos = 3;
	int yPos = 0;

	bool isOnGround = false;
	bool rotateLast = false;

	/**
	 * Rotate the top left corner array of Tetromino in specified direction.
	 *
	 * \param arr Array
	 * \param size Size of the square. (Max:4)
	 * \param rDir Direction of rotation
	 */
	void rotateArray(array<array<int, 4>, 4>& arr, int size, Rotational_Direction rDir);

public:
	Tetromino(Type type);
	Tetromino(Type type, bool isGhost);
	~Tetromino();

	/**
	 * Get the ghost of the current tetromino.
	 *
	 * \param board Board that the tetromino is on
	 * \return A copy tetromino of the current tetromino with ghost color and hard drop on the board
	 */
	Tetromino getGhost(Board& board);

	/**
	 * Make the tetromino have the ghost color.
	 *
	 */
	void turnToGhostColor();

	/**
	 * Rotate the tetromino on the board. Wall kick is implemented
	 *
	 * \param rDir Direction of rotation
	 * \param board Board the tetromino is on
	 * \return true if succeed, false otherwise
	 */
	bool rotate(Rotational_Direction rDir, Board& board);

	/**
	 * Set xPos and yPos. (Only set the variable, not on the actual board)
	 *
	 * \param xPos
	 * \param yPos
	 * \param board To be placed on
	 * \return true if succeed, false otherwise
	 */
	bool setXY(int xPos, int yPos, Board& board);
	void setXY(int xPos, int yPos);

	/**
	 * Hard drop the tetromino on the board.
	 *
	 * \return number of cells dropped
	 * \param board To be placed on
	 */
	int hardDrop(Board& board);

	/**
	 * Set the tetromino on the board.
	 *
	 * \param board To be placed on
	 */
	void setPiece(Board& board);

	/**
	 * Check if tetromino is touching the ground or hanging.
	 *
	 * \param board
	 * \return true if tetromino on ground or hanging, false otherwise
	 */
	bool checkIsOnGround(Board& board);


	//void softDrop();

	/**
	 * Move tetromino in the specified direction 1 space.
	 *
	 * \param dir Direction of moving
	 * \param board
	 * \return true if succeed, false otherwise
	 */
	bool move(Moving_Direction dir, Board& board);

	/**
	 * Check if there is a collision between tetromino and board.
	 *
	 * \param xPos
	 * \param yPos
	 * \param cells Array of tetromino
	 * \param board
	 * \return true if there's no collision, false if it is
	 */
	bool checkCollision(int xPos, int yPos, Board& board);

	/**
	 * Check if there is a collision between tetromino and board.
	 *
	 * \param board
	 * \return true if there's no collision, false if it is
	 */
	bool checkCollision(Board& board);

	std::array<int, 3>  firstPossibleMoveNoRo(Board& board);
	std::array<int, 4>  firstPossibleMove(Board& board);

	/**
	 * Render tetromino with the board position.
	 *
	 * \param window
	 * \param board
	 */
	void render(RenderWindow& window, Board& board);
	void setTransparency(sf::Uint8 transparency);
	void renderBorder(RenderWindow& window, Board& board, Color color);

	/**
	 * Render tetromino with a definite x and y on the window.
	 *
	 * \param window
	 * \param x
	 * \param y
	 */
	void render(RenderWindow& window, int x, int y);

	/**
	 * Reset back to spawn condition.
	 */
	void reset();

	/**
	 * Get tetromino's type.
	 *
	 * \return The type of the tetromino
	 */
	Type getType();

	/**
	 * Get the current orientation of tetromino.
	 *
	 * \return The orientation of tetromino
	 */
	Orientation getOrientation();

	int getXPos();
	int getYPos();

	/**
	 * Check if the last move is a rotation.
	 *
	 * \return rotateLast
	 */
	bool getRotateLast();


	int getMinX();
	int getMinY();
	int getMaxX();
	int getMaxY();

};

#endif