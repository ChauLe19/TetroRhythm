#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "Board.h"
#include "Settings.h"
#include "Tetromino.h"
#include "StateScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <iterator>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <cstdlib>      // std::rand, std::srand
#include <ctime>        // std::time
#include <fstream>

using namespace sf;

const int boardX = 100;
const int boardY = 100;



class GameBase : public StateScreen
{
protected:
	typedef Settings::Controls_Settings Controls_Settings;
	Controls_Settings& settings;
	Text text;
	Font font;
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
	int frameCount = 0;
	int onGroundCount = 0;
	bool isGameOver = false;
	SoundBuffer buffer;
	Sound sound;
	ifstream inFile;
	int nextBeatTimeMS = 0;
	array<Keyboard::Key, 8>& keyMap;
	int& delayAutoShift;
	int& autoRepeatRate;
	int delayAutoShiftCount = 0;
	int autoRepeatRateCount = 0;
	Keyboard::Key holdKey;
	Keyboard::Key currentKey;
	bool isAutoShiftActive = false;
	bool isAutoRepeatActive = false;
	bool firstPressed = false;
public:
	GameBase(Controls_Settings& settings);
	~GameBase();
	//Tetromino& nextPiece();
	void run(RenderWindow& window);
	virtual void tick(RenderWindow& window);
	ClearType determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType);
	static ClearType determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType, Board board);
	int getScore();
	void hold();
	void run();
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
	void pause();
	void start();
	void restart();
	void reset();
	bool getIsGameOver();
	void gameOver();
	static int convertClearTypeToScores(ClearType type);
	Sound& getSound();
	virtual void dropOnBeat() = 0;
	virtual void keyEvent(State& state, Keyboard::Key key);
};
#endif
