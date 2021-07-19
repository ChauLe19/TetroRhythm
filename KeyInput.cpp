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
	// TODO: does this copy or refer?
	Tetromino& currentPiece = game.getCurrentPiece();
	Tetromino& prevPiece = game.getCurrentPiece();
	Board& board = game.getBoard();
	switch (currentKey)
	{
	case Keyboard::F:
		 currentPiece.rotate(Rotational_Direction::CW, board);
		break;
	case Keyboard::A:
		currentPiece.rotate(Rotational_Direction::CCW, board);
		break;
	case Keyboard::S:
		currentPiece.rotate(Rotational_Direction::R180, board);
		break;
	case Keyboard::L:
		currentPiece.move(Moving_Direction::RIGHT_DIR, board);
		break;
	case Keyboard::J:
		currentPiece.move(Moving_Direction::LEFT_DIR, board);
		break;
	case Keyboard::K:
		if (currentPiece.move(Moving_Direction::DOWN_DIR, board)) 
			game.setScore( game.getScore() + Game::convertClearTypeToScores(ClearType::SOFTDROP));
		break;
	case Keyboard::I:
		currentPiece.hardDrop(board);
		cout << "input" << endl;
		board.print();
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
	}

	if (game.getPrevPiecePtr() != nullptr)
	{
		cout << "Clearing" << endl;
		// TODO: copy board before clear, is this optimized???
		Board tempBoard = board;
		ClearingInfo tempClearingInfo = board.clearLines();
		ClearType tempScoresType = Game::determineClearType(prevPiece, tempClearingInfo, game.getPrevClearType(), tempBoard);
		if (tempScoresType != ClearType::NONE)
		{
			game.setPrevClearType(tempScoresType);
		}
		game.setScore(game.getScore() + Game::convertClearTypeToScores(tempScoresType));
	}
}

void KeyInput::updateKeyEvent(Keyboard::Key key)
{
	currentKey = key;
}
