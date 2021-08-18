/*****************************************************************//**
 * \file   GameBase.h
 * \brief  Perform and render Tetris type game functionalities. No rulesets included.
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
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
#include <string>
#include <filesystem>

using namespace sf;
namespace fs = std::filesystem;

const int boardX = 1024- 45*5;
const int boardY = 100;

// frame per cell. how many frame in between dropping 1 cell
//https://tetris.wiki/Marathon
//TODO: change to float
const int levelSpeed[15] = { 60, 58, 37, 28, 21, 16, 11, 8, 6, 4, 3, 2, 1, 1, 1 };
/**
 * Class for general Tetris controls and mechanics.
 */
class GameBase : public StateScreen
{
protected:
	static const int squareSize = 45;
	Text text;
	Font font;
	SoundBuffer buffer;
	Sound sound;
	ifstream inFile;

	// Objects in game
	//**************************************

	list<Tetromino*> bag;
	list<int> beatsTime;
	Tetromino* prevPiecePtr;
	Tetromino* currentPiecePtr;
	Tetromino* holdPiecePtr;
	Tetromino* ghostPiece;
	ClearType prevClearType = ClearType::NONE;
	Board* boardPtr;
	Board board;
	list<int>::iterator beatIt;

	// Game status
	//*************************************

	int level = 1;
	int score = 0;
	int frameCount = 0;
	int onGroundCount = 0;
	bool isGameOver = false;
	int nextBeatTimeMS = 0;
	int rainbowIndex = 0;
	int linesCleared = 0;
	int clearTypeCounter = 0;

	// Controls related variables
	//****************************************

	typedef Settings::Controls_Settings Controls_Settings;
	Controls_Settings& settings;
	map<string, Keyboard::Key>& keybinds;
	Keyboard::Key holdKey;
	Keyboard::Key currentKey;
	int& delayAutoShift;
	int& autoRepeatRate;
	int delayAutoShiftCount = 0;
	int autoRepeatRateCount = 0;
	bool isAutoShiftActive = false;
	bool isAutoRepeatActive = false;
	bool firstPressed = false;
	bool alreadyHold = false;

	//Softdrop DAS
	int SDdelayAutoShiftCount = 0;
	int SDautoRepeatRateCount = 0;
	bool SDisAutoShiftActive = false;
	bool SDisAutoRepeatActive = false;
	bool SDfirstPressed = false;
	bool SDalreadyHold = false;



	static bool isB2BChain(ClearType type);
	static int getTSpinType(Tetromino piece, Board& board);
public:
	GameBase(Controls_Settings& settings);
	GameBase(Controls_Settings& settings, string folderPath);
	~GameBase();

	// State Screen functions
	//***************************************************

	virtual void tick(RenderWindow& window);
	virtual void render(RenderWindow& window);
	virtual void keyEvent(State& state, Keyboard::Key key);
	virtual void mouseEvent(RenderWindow& window);

	void renderBeatSignal(RenderWindow& window);

	/**
	 * Convert the clear type to the appropriate score.
	 *
	 * \param type Clearing lines type
	 * \return The score for the clear type
	 */
	static int convertClearTypeToScores(ClearType type);


	/**
	 * Determine clear type based on the piece type
	 * and how many lines it cleared and the board before clearing.
	 * And determine whether if it's a B2B clear or not.
	 *
	 * \param clearingPiece Piece used for clearing
	 * \param info Contains how many lines it cleared and if whether was a Perfect Clear
	 * \param prevClearType Previous clearing type
	 * \param board Board before clearing
	 * \return Clear lines type
	 */
	static ClearType determineClearType(Tetromino clearingPiece, ClearingInfo info, ClearType prevClearType, Board board);

	string clearTypeToString(ClearType clearType);


	/**
	 * Discard previous piece and pick a tetromino from the bag.
	 *
	 * \return The next Tetromino
	 */
	Tetromino& nextPiece();


	/**
	 * Hold piece functionality. Can't hold twice in a row.
	 *
	 */
	void hold();

	void pause();
	void start();
	void reset();
	void restart();
	void gameOver();


	// Getters and Setters
	//*******************************************

	int getScore();

};
#endif
