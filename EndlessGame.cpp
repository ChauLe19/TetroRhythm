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

void EndlessGame::tick(State& state, RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(state, window);
	frameCount++;
	// restart song if not game over
	if (!isGameOver && sound.getStatus() == SoundSource::Status::Stopped)
	{
		sound.play();
	}

	/*if (frameCount >= levelSpeed[level - 1])
	{
		currentPiecePtr->move(Moving_Direction::DOWN_DIR, board);
		frameCount = 0;
	}*/


	//if (currentPiecePtr->checkIsOnGround(board))
	//{
	//	onGroundCount++;
	//	if (onGroundCount > 100)
	//	{
	//		currentPiecePtr->hardDrop(board);
	//		// TODO: copy board before clear, is this optimized???
	//		Board tempBoard = board;
	//		prevPiecePtr = currentPiecePtr;
	//		ClearingInfo tempClearingInfo = board.clearLines();
	//		linesCleared += tempClearingInfo.linesCleared;
	//		level = clamp(linesCleared / 10 + 1, 1, 15);

	//		ClearType tempScoresType = determineClearType(*prevPiecePtr, tempClearingInfo, prevClearType, tempBoard);

	//		if (tempScoresType != ClearType::NONE)
	//		{
	//			prevClearType = tempScoresType;
	//			clearTypeCounter = 60; // 1 second display
	//		}
	//		score += convertClearTypeToScores(tempScoresType);
	//		//currentPiecePtr = &nextPiece();
	//		nextPiece();
	//		alreadyHold = false;
	//		onGroundCount = 0;
	//	}
	//}
}

void EndlessGame::tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr)
{
	tick(state, window);
}

void EndlessGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
}

void EndlessGame::mouseEvent(State& state, RenderWindow& window)
{
	if (!isGameOver) return;
	GameBase::mouseEvent(state, window);
}

void EndlessGame::render(RenderWindow& window)
{
	GameBase::render(window);

	text.setString("Level: " + to_string(level));
	text.setPosition(650, 500);
	window.draw(text);

	if (isGameOver)
	{
		GameBase::renderGameOver(window);

		text.setCharacterSize(80);
		text.setFillColor(Color::White);
		text.setString(to_string(score));
		text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 250);
		window.draw(text);
	}
}
