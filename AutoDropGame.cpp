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


	if (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS && beatIt != beatsTime.end())
	{

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

		while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS)
		{
			++beatIt;
			if (beatIt == beatsTime.end()) break;
			nextBeatTimeMS = *beatIt;
		}
	}
}

void AutoDropGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
}

void AutoDropGame::render(RenderWindow& window)
{
	GameBase::render(window);
}
