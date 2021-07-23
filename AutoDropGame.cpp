#include "AutoDropGame.h"

AutoDropGame::AutoDropGame(Controls_Settings& settings) : GameBase(settings)
{
}

AutoDropGame::~AutoDropGame()
{
}

void AutoDropGame::tick(RenderWindow& window)
{
	GameBase::tick(window);
	
	dropOnBeat();

}

void AutoDropGame::dropOnBeat()
{
	if (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS)
	{
		//cout << nextBeatTimeMS << endl;
		// hard drop current piece
		currentPiecePtr->hardDrop(board);
		// TODO: copy board before clear, is this optimized???
		Board tempBoard = board;
		prevPiecePtr = currentPiecePtr;
		ClearingInfo tempClearingInfo = board.clearLines();
		ClearType tempScoresType = determineClearType(*prevPiecePtr, tempClearingInfo, prevClearType, tempBoard);

		if (tempScoresType != ClearType::NONE)
		{
			prevClearType = tempScoresType;
		}
		score += convertClearTypeToScores(tempScoresType);
		//currentPiecePtr = &nextPiece();
		nextPiece();
		alreadyHold = false;
		onGroundCount = 0;

		do
		{
			char beat[10];
			inFile.getline(beat, 10, '\r');
			nextBeatTimeMS = atoi(beat);
		} while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS); // if the time is too tight, skip to the next
		return;
	}
}

void AutoDropGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
}
