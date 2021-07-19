#ifndef TETROMINO_H
#define TETROMINO_H

#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
using namespace std;
enum class Type { I = 0, O = 1, T = 2, S = 3, Z = 4, J = 5, L = 6 };
enum class Orientation { SPAWN = 0, RIGHT = 1, FLIP = 2, LEFT = 3 };
enum class Rotational_Direction { CCW = -1, NORO = 0, CW = 1, R180 = 2 };
enum class Moving_Direction { UP_DIR = 0, LEFT_DIR = 1, RIGHT_DIR = 2, DOWN_DIR = 3 };
const static vector<Type> allPieces{ Type::I, Type::O, Type::T, Type::S, Type::Z,Type::J,Type::L };



const static std::array<std::array<std::array<int, 4>, 4>, 7> tetrominos = { {
											{{  //I block
												{0, 0, 0, 0},
												{1, 1, 1, 1},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //O block
												{2, 2, 0, 0},
												{2, 2, 0, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //T block
												{0, 3, 0, 0},
												{3, 3, 3, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //S block
												{0, 4, 4, 0},
												{4, 4, 0, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //Z block
												{5, 5, 0, 0},
												{0, 5, 5, 0}
											}},
											{{  //J block
												{6, 0, 0, 0},
												{6, 6, 6, 0},
												{0, 0, 0, 0},
												{0, 0, 0, 0}
											}},
											{{  //L block
												{0, 0, 7, 0},
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

class Tetromino
{
private:
	array<array<int, 4>, 4> cells = { 0 };
	Type type;
	int xPos = 3;
	int yPos = 0;
	bool isOnGround = false;
	bool rotateLast = false;
	Texture cellsTexture;
	Sprite cellImage;
	Orientation orientation = Orientation::SPAWN;
	//bool setXY(int xPos, int yPos, Orientation orientation);
	//bool setXY(int xPos, int yPos, Rotational_Direction rDir);
	void rotateArray(array<array<int, 4>, 4>& arr, int size, Rotational_Direction rDir);

public:
	Tetromino(Type type);
	Tetromino(Type type, bool isGhost);
	Tetromino();
	~Tetromino();

	Tetromino getGhost(Board& board);
	bool setXY(int xPos, int yPos, Board& board);
	void turnToGhostColor();
	bool rotate(Rotational_Direction rDir, Board& board);
	void hardDrop(Board& board);
	void setPiece(Board& board);
	bool checkIsOnGround(Board& board);
	bool getIsOnGround(Board& board);
	void softDrop();
	bool move(Moving_Direction dir, Board& board);
	bool checkCollision(int xPos, int yPos, array<array<int, 4>, 4> cells, Board& board);
	bool checkCollision(Board& board);
	void render(RenderWindow& window, Board& board);
	void render(RenderWindow& window, int x, int y);
	void reset();
	Type getType();
	int getXPos();
	int getYPos();
	Orientation getOrientation();
	bool getRotateLast();
};

#endif