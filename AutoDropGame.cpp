#include "AutoDropGame.h"

AutoDropGame::AutoDropGame(Controls_Settings& settings) : GameBase(settings)
{
}
AutoDropGame::AutoDropGame(Controls_Settings& settings, string folderPath) : GameBase(settings, folderPath)
{
}

AutoDropGame::~AutoDropGame()
{
}

void AutoDropGame::tick(State& state, RenderWindow& window)
{
	if (isGameOver) return;
	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		gameOver();
		finished = true;
		return;
	}
	GameBase::tick(state, window);


	dropOnBeat();


}

void AutoDropGame::tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr)
{
	tick(state, window);
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
			clearTypeCounter = 60; // 1 second display
		}
		score += convertClearTypeToScores(tempScoresType);
		//currentPiecePtr = &nextPiece();
		nextPiece();
		alreadyHold = false;
		onGroundCount = 0;

		++beatIt;
		rainbowIndex = (rainbowIndex + 1) % 7;
		if (beatIt == beatsTime.end()) return;
		nextBeatTimeMS = *beatIt;
	}
}

void AutoDropGame::keyEvent(State& state, Keyboard::Key key)
{
	// can't hard drop in this mode
	if (key == keybinds["HARD_DROP"]) return;
	GameBase::keyEvent(state, key);
}

void AutoDropGame::mouseEvent(State& state, RenderWindow& window, Event event)
{
	if (!isGameOver && Mouse::isButtonPressed(Mouse::Right)) return;
	GameBase::mouseEvent(state, window, event);
}

void AutoDropGame::render(RenderWindow& window)
{
	GameBase::render(window);
	GameBase::renderBeatSignal(window);
	if (isGameOver)
	{
		GameBase::renderGameOver(window);

		text.setCharacterSize(120);
		text.setFillColor(finished ? Color::Green : Color::Red);
		text.setString(finished ? "Completed" : "Failed");
		text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 400);
		window.draw(text);

		text.setCharacterSize(80);
		text.setFillColor(Color::White);
		text.setString(to_string(score));
		text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 250);
		window.draw(text);
	}
}
