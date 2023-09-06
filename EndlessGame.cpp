#include "EndlessGame.h"

//TODO: speed depends on the song speed. the song speed up after every round
EndlessGame::EndlessGame(StateManager &stateManager, string folderPath) : GameBase(stateManager, folderPath)
{
}

EndlessGame::~EndlessGame()
{
}

void EndlessGame::tick(const float & dt, RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(dt, window);
	frameCount++;
	// restart song if not game over
	if (!isGameOver && sound.getStatus() == SoundSource::Status::Stopped)
	{
		sound.play();
	}
}

void EndlessGame::gameOver()
{
	GameBase::gameOver();
	highscores->endless = max(highscores->endless, score);
	GameSettings::saveHighscores();
}

void EndlessGame::keyEvent(const float & dt, Event event)
{
	GameBase::keyEvent(dt, event);
}

void EndlessGame::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	GameBase::mouseEvent(dt, window, event);
	if (isGameOver && !hsSaved)
	{
		hsSaved = true;
	}
}

void EndlessGame::render(RenderWindow& window)
{
	GameBase::render(window);

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
