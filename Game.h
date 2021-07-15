#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Tetromino.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <iterator>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace sf;

const int boardX = 100;
const int boardY = 100;
class Game
{
private:
	//list<Tetromino> bag;
	Board board=Board(boardX,boardY);
	Tetromino currentPiece = Tetromino(Type::T);
	Tetromino holdPiece = Tetromino(Type::T);
public:
	Game();
	Tetromino& nextPiece();
	void run(RenderWindow& window);
	~Game();
	void run();
	void tick();
	void render(RenderWindow& window);

};
#endif
