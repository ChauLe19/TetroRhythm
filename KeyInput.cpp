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

void KeyInput::tick(State& state, Game& game)
{
	if (state != State::GAME) return;
	if (game.getIsGameOver()) return;

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

	if (currentKey == keyMap[static_cast<int> (Controls_Key::MOVE_RIGHT)])
	{
		if (isAutoRepeatActive && autoRepeatRate == 0)
			while (currentPiece.move(Moving_Direction::RIGHT_DIR, board));
		else
			currentPiece.move(Moving_Direction::RIGHT_DIR, board);
	}
	else if (currentKey == keyMap[static_cast<int> (Controls_Key::MOVE_LEFT)])
	{
		if (isAutoRepeatActive && autoRepeatRate == 0)
			while (currentPiece.move(Moving_Direction::LEFT_DIR, board));
		else
			currentPiece.move(Moving_Direction::LEFT_DIR, board);
	}
	else if (currentKey == keyMap[static_cast<int> (Controls_Key::SOFT_DROP)])
	{
		if (currentPiece.move(Moving_Direction::DOWN_DIR, board))
			game.setScore(game.getScore() + Game::convertClearTypeToScores(ClearType::SOFTDROP));
	}


	//switch (currentKey)
	//{
	//	/*case Keyboard::F:
	//		currentPiece.rotate(Rotational_Direction::CW, board);
	//		break;
	//	case Keyboard::A:
	//		currentPiece.rotate(Rotational_Direction::CCW, board);
	//		break;*/
	//case Keyboard::S:
	//	currentPiece.rotate(Rotational_Direction::R180, board);
	//	break;
	//case Keyboard::L:
	//	if (isAutoRepeatActive && autoRepeatRate == 0)
	//		while (currentPiece.move(Moving_Direction::RIGHT_DIR, board));
	//	else
	//		currentPiece.move(Moving_Direction::RIGHT_DIR, board);
	//	break;
	//case Keyboard::J:
	//	if (isAutoRepeatActive && autoRepeatRate == 0)
	//		while (currentPiece.move(Moving_Direction::LEFT_DIR, board));
	//	else
	//		currentPiece.move(Moving_Direction::LEFT_DIR, board);
	//	break;
	//case Keyboard::K:
	//	if (currentPiece.move(Moving_Direction::DOWN_DIR, board))
	//		game.setScore(game.getScore() + Game::convertClearTypeToScores(ClearType::SOFTDROP));
	//	break;
	//}

}

void KeyInput::updateKeyEvent(State& state, Keyboard::Key key)
{
	if (state != State::GAME) return;
	// No hold key control (rotation)
	if (key == keyMap[static_cast<int> (Controls_Key::ROTATE_CW)]
		|| key == keyMap[static_cast<int> (Controls_Key::ROTATE_CCW)]
		|| key == keyMap[static_cast<int> (Controls_Key::HARD_DROP)]
		|| key == keyMap[static_cast<int> (Controls_Key::HOLD)]) return;
	currentKey = key;
	firstPressed = true;
	isAutoShiftActive = false;
}

void KeyInput::noHoldKeyEvent(State& state, Keyboard::Key key, Game& game, Config& config)
{
	if (state == State::MENU)
	{
		switch (key)
		{
		case Key::Enter:
			game.start();
			state = State::GAME;
			break;
		case Key::C:
			state = State::SETTINGS;
			break;
		}
	}
	else if (state == State::SETTINGS)
	{
		if (config.getIsChanging())
		{
			config.changeKey(key, keyMap);
			return;
		}
		switch (key)
		{
		case Key::Escape:
			state = State::MENU;
			break;
		case Key::Down:
			config.setCursor(config.getCursor() + 1);
			break;
		case Key::Up:
			config.setCursor(config.getCursor() - 1);
			break;
		case Key::Enter:
			config.waitForChangingKey();
			break;
		}
	}
	else if (state == State::GAME)
	{
		Tetromino& currentPiece = game.getCurrentPiece();
		Board& board = game.getBoard();
		//switch (key)
		//{
		//case Keyboard::Escape:
		//	game.reset();
		//	state = State::MENU;
		//	break;
		//case Keyboard::F:
		//	currentPiece.rotate(Rotational_Direction::CW, board);
		//	break;
		//case Keyboard::A:
		//	currentPiece.rotate(Rotational_Direction::CCW, board);
		//	break;
		//case Keyboard::R:
		//	game.restart();
		//	break;
		//case Keyboard::I:
		//	currentPiece.hardDrop(board);
		//	//cout << "input" << endl;
		//	//board.print();
		//	game.setScore(game.getScore() + Game::convertClearTypeToScores(ClearType::HARDDROP));

		//	game.nextPiece();

		//	currentPiece.checkIsOnGround(board);
		//	//alreadyHold = false;
		//	//onGroundCount = 0;
		//	game.resetOnGroundCount();
		//	break;
		//case Keyboard::D:
		//	game.hold();
		//	break;
		//case Keyboard::P:
		//	cout << "playing:" << game.getSound().getPlayingOffset().asMilliseconds() << endl;
		//	break;
		//}

		if (key == Keyboard::Escape)
		{
			game.reset();
			state = State::MENU;
		}
		else if (key == keyMap[static_cast<int> (Controls_Key::ROTATE_CW)])
		{
			currentPiece.rotate(Rotational_Direction::CW, board);
		}
		else if (key == keyMap[static_cast<int> (Controls_Key::ROTATE_CCW)])
		{
			currentPiece.rotate(Rotational_Direction::CCW, board);
		}
		else if (key == Keyboard::R)
		{
			game.restart();
		}
		else if (key == keyMap[static_cast<int> (Controls_Key::ROTATE_180)])
		{
			currentPiece.rotate(Rotational_Direction::R180, board);
		}
		else if (key == keyMap[static_cast<int> (Controls_Key::HARD_DROP)])
		{
			currentPiece.hardDrop(board);
			//cout << "input" << endl;
			//board.print();
			game.setScore(game.getScore() + Game::convertClearTypeToScores(ClearType::HARDDROP));

			game.nextPiece();

			currentPiece.checkIsOnGround(board);
			//alreadyHold = false;
			//onGroundCount = 0;
			game.resetOnGroundCount();
		}
		else if (key == keyMap[static_cast<int> (Controls_Key::HOLD)])
		{
			game.hold();
		}
		else if (key == Keyboard::R)
		{
			cout << "playing:" << game.getSound().getPlayingOffset().asMilliseconds() << endl;
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

	}

	array<Keyboard::Key, 8>& KeyInput::getKeyMap()
	{
		return keyMap;
	}
