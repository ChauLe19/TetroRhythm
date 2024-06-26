/*****************************************************************//**
 * \file   GameBase.h
 * \brief  Perform and render Tetris type game functionalities. No rulesets included.
 *
 * \author Chau Le
 * \date   July 2021
 *********************************************************************/
#pragma once
#ifndef GAME_BASE_H
#define GAME_BASE_H

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

#include "Board.h"
#include "Tetromino.h"
#include "StateScreen.h"
#include "StateManager.h"
#include "GameSettings.h"

#define inputThickness 5

namespace fs = std::filesystem;

//const int boardX = 1024- 45*5;
const int boardX = 1024 - boardSquareSize* boardWidth/2;
const int boardY = 576 - boardSquareSize * boardHeight/2;

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
	std::string songName; // the folder will have the same name
	sf::Text text;
	sf::SoundBuffer buffer;
	sf::SoundBuffer sfxBuffer;
	sf::Sound sound;
	sf::Sound sfx;
	sf::Sprite songBackground;

	// Objects in game
	//**************************************

	std::list<Tetromino*> bag;
	Tetromino* prevPiecePtr;
	Tetromino* currentPiecePtr;
	Tetromino* holdPiecePtr;
	Tetromino ghostPiece = Tetromino(Type::I);
	ClearType prevClearType = ClearType::NONE; // only records the clear type when the player actually clear line(s)
	ClearType recentClearType = ClearType::NONE; // records the clear type even when player didn't clear any lines
	Board* boardPtr;
	Board board;

	// Game status
	//*************************************

	int level = 1;
	int score = 0;
	int frameCount = 0;
	int onGroundCount = 0;
	bool isGameOver = false;
	int rainbowIndex = 0;
	int linesCleared = 0;
	int clearTypeCounter = 0;
	bool finished = false;

	int lastX = 0;
	int lastY = 0;

	// Controls related variables
	//****************************************

	sf::Keyboard::Key holdKey;
	sf::Keyboard::Key currentKey;
	GameSettings::Controls_Settings* controlsSettings = GameSettings::getInstance()->getSettings();
	GameSettings::Highscores* highscores = GameSettings::getInstance()->getHighscores();
	bool firstPressed = false;
	bool alreadyHold = false;
	bool locked = false;
	bool keyMouseRegistered = false;
	bool keyMouseReleased = false;
	sf::VertexArray inputVertex = sf::VertexArray(sf::PrimitiveType::Quads);
	sf::Vector2i lastMousePos = sf::Vector2i(0,0);

	static bool isB2BChain(ClearType type);
	static int getTSpinType(Tetromino piece, Board& board);

protected:
	void clearLines();

public:
	GameBase(StateManager& stateManager, std::string folderPath);
	~GameBase();

	// State Screen functions
	//***************************************************

	virtual void tick(const float & dt, sf::RenderWindow& window);
	virtual void render(sf::RenderWindow& window);
	virtual void keyEvent(const float & dt, sf::Event event);
	virtual void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
	virtual void mouseScrollEvent(sf::Event event);

	void renderGameOver(sf::RenderWindow& window);

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

	std::string clearTypeToString(ClearType clearType);


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
	virtual void restart();
	virtual void gameOver();
	bool createGarbageLine(int holePos);


	// Getters and Setters
	//*******************************************

	int getScore();

private:
	std::array<int, 2> findNearestPossiblePlacement(sf::RenderWindow& window, Tetromino& piece, Board& board);
};
#endif
