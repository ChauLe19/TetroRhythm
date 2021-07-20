#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Tetromino.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <iterator>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <cstdlib>      // std::rand, std::srand
#include <ctime>        // std::time

using namespace sf;

const int boardX = 100;
const int boardY = 100;



class Game
{
private:
	list<Tetromino*> bag;
	int score = 0;
	ClearType prevClearType = ClearType::NONE;
	//Board board = Board(boardX, boardY);
	Board* boardPtr;
	Board board;
	bool alreadyHold = false;
	Tetromino* prevPiecePtr;
	Tetromino* currentPiecePtr;
	Tetromino* holdPiecePtr;
	Tetromino* ghostPiece;
	//int frameCount = 0;
	int onGroundCount = 0;
	bool isGameOver = false;
	SoundBuffer buffer;
	Sound sound;
public:
	Game();
	~Game();
	//Tetromino& nextPiece();
	void run(RenderWindow& window);
	void tick(RenderWindow& window);
	ClearType determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType);
	static ClearType determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType, Board board);
	int getScore();
	void hold();
	void run();
	//void tick();
	void render(RenderWindow& window);
	Tetromino* getCurrentPiecePtr();
	Tetromino* getPrevPiecePtr();
	Tetromino& getCurrentPiece();
	Tetromino& getPrevPiece();
	void setPrevPiecePtr(Tetromino* piece);
	void setCurrentPiecePtr(Tetromino* piece);
	ClearType getPrevClearType();
	void setPrevClearType(ClearType type);
	Board& getBoard();
	Board* getBoardPtr();
	Tetromino& nextPiece();
	void increaseOnGroundCount();
	void resetOnGroundCount();
	void setScore(int score);
	void restart();
	bool getIsGameOver();
	static int convertClearTypeToScores(ClearType type);
	void tick(RenderWindow& window, int& frameCount);
};
#endif
