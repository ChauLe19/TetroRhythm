#include "KeyInput.h"

KeyInput::KeyInput()
{
}

//KeyInput::KeyInput(Game& game)
//{
//}

KeyInput::~KeyInput()
{
}

void KeyInput::tick(Game& game)
{
	if (game.getIsGameOver()) return;
	// TODO: does this copy or refer?
	Tetromino& currentPiece = game.getCurrentPiece();
	Tetromino& prevPiece = game.getCurrentPiece();
	Board& board = game.getBoard();

	if (Keyboard::isKeyPressed(currentKey))
	{
		//cout << "DAS count:" << delayAutoShiftCount << endl;
		if (firstPressed)
		{
			firstPressed = false;
			isAutoRepeatActive = false;
			isAutoShiftActive = true;
			delayAutoShiftCount = 0;
			autoRepeatRateCount = 0;
		}
		else if (isAutoRepeatActive)
		{
			if (autoRepeatRateCount < autoRepeatRate)
			{
				autoRepeatRateCount++;
				return;
			}
			else
			{
				autoRepeatRateCount = 0;
			}
		}
		else if (isAutoShiftActive)
		{
			delayAutoShiftCount++;
			if (delayAutoShiftCount >= delayAutoShift)
			{
				isAutoRepeatActive = true;
			}
			return;
		}

	}
	else // not holding
	{
		delayAutoShiftCount = 0;
		autoRepeatRateCount = 0;
		isAutoRepeatActive = false;
		isAutoShiftActive = false;
		return;
	}

	switch (currentKey)
	{
		/*case Keyboard::F:
			currentPiece.rotate(Rotational_Direction::CW, board);
			break;
		case Keyboard::A:
			currentPiece.rotate(Rotational_Direction::CCW, board);
			break;*/
	case Keyboard::S:
		currentPiece.rotate(Rotational_Direction::R180, board);
		break;
	case Keyboard::L:
		if (isAutoRepeatActive && autoRepeatRate == 0) 
			while (currentPiece.move(Moving_Direction::RIGHT_DIR, board));
		else
			currentPiece.move(Moving_Direction::RIGHT_DIR, board);
		break;
	case Keyboard::J:
		if (isAutoRepeatActive && autoRepeatRate == 0)
			while (currentPiece.move(Moving_Direction::LEFT_DIR, board));
		else
		currentPiece.move(Moving_Direction::LEFT_DIR, board);
		break;
	case Keyboard::K:
		if (currentPiece.move(Moving_Direction::DOWN_DIR, board))
			game.setScore(game.getScore() + Game::convertClearTypeToScores(ClearType::SOFTDROP));
		break;
	}

}

void KeyInput::updateKeyEvent(Keyboard::Key key)
{
	// No hold key control (rotation)
	if (key == Keyboard::F || key == Keyboard::A || key == Keyboard::I || key == Keyboard::D) return;
	currentKey = key;
	firstPressed = true;
	isAutoShiftActive = false;
}

void KeyInput::noHoldKeyEvent(Keyboard::Key key, Game& game)
{

	Tetromino& currentPiece = game.getCurrentPiece();
	Board& board = game.getBoard();
	switch (key)
	{
	case Keyboard::F:
		currentPiece.rotate(Rotational_Direction::CW, board);
		break;
	case Keyboard::A:
		currentPiece.rotate(Rotational_Direction::CCW, board);
		break;
	case Keyboard::R:
		game.restart();
		break;
	case Keyboard::I:
		currentPiece.hardDrop(board);
		//cout << "input" << endl;
		//board.print();
		game.setScore(game.getScore() + Game::convertClearTypeToScores(ClearType::HARDDROP));

		game.nextPiece();

		currentPiece.checkIsOnGround(board);
		//alreadyHold = false;
		//onGroundCount = 0;
		game.resetOnGroundCount();
		break;
	case Keyboard::D:
		game.hold();
		break;
	case Keyboard::P:
		cout << "playing:" << game.getSound().getPlayingOffset().asMilliseconds() << endl;
		break;
	}
	if (game.getPrevPiecePtr() != nullptr)
	{
		//cout << "Clearing" << endl;
		// TODO: copy board before clear, is this optimized???
		Board tempBoard = board;
		ClearingInfo tempClearingInfo = board.clearLines();
		ClearType tempScoresType = Game::determineClearType(game.getPrevPiece(), tempClearingInfo, game.getPrevClearType(), tempBoard);
		if (tempScoresType != ClearType::NONE)
		{
			game.setPrevClearType(tempScoresType);
		}
		game.setScore(game.getScore() + Game::convertClearTypeToScores(tempScoresType));
	}

}
