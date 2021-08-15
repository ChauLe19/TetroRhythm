#include "EndlessGame.h"

//TODO: speed depends on the song speed. the song speed up after every round
EndlessGame::EndlessGame(Controls_Settings& settings) : GameBase(settings)
{
}
EndlessGame::EndlessGame(Controls_Settings& settings, string folderPath) : GameBase(settings, folderPath)
{
}

EndlessGame::~EndlessGame()
{
}

void EndlessGame::tick(RenderWindow& window)
{
	frameCount++;
	// restart song if not game over
	if (!isGameOver && sound.getStatus() == SoundSource::Status::Stopped)
	{
		sound.play();
	}

	if (frameCount >= levelSpeed[level-1])
	{
		currentPiecePtr->move(Moving_Direction::DOWN_DIR, board);
		frameCount = 0;
	}

	GameBase::tick(window);

	if (currentPiecePtr->checkIsOnGround(board))
	{
		onGroundCount++;
		if (onGroundCount > 100)
		{
			currentPiecePtr->hardDrop(board);
			// TODO: copy board before clear, is this optimized???
			Board tempBoard = board;
			prevPiecePtr = currentPiecePtr;
			ClearingInfo tempClearingInfo = board.clearLines();
			linesCleared += tempClearingInfo.linesCleared;
			level = clamp(linesCleared / 10 + 1, 1, 15);

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

void EndlessGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
}

void EndlessGame::render(RenderWindow& window)
{
	GameBase::render(window);
	
	text.setString("Level: " + to_string(level));
	text.setPosition(700, 500);
	window.draw(text);
}
