#include "AutoDropGame.h"

void AutoDropGame::tick(RenderWindow& window, int& frameCount)
{
	if (isGameOver) return;
	if (frameCount >= 48)
	{
		currentPiecePtr->move(Moving_Direction::DOWN_DIR, board);
		frameCount = 0;
	}
	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		gameOver();
	}


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
	/*cout << "GAME BOARD" << endl;
	board.print();*/

	if (currentPiecePtr->getIsOnGround(board))
	{
		onGroundCount++;
		if (onGroundCount > 100)
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
		}
	}
}

void AutoDropGame::dropOnBeat()
{
}
