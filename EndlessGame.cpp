#include "EndlessGame.h"

//TODO: speed depends on the song speed. the song speed up after every round
EndlessGame::EndlessGame(StateManager &stateManager, string folderPath) : GameBase(stateManager, folderPath)
{
}

EndlessGame::~EndlessGame()
{
}

void EndlessGame::tick(RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(window);
	frameCount++;
	// restart song if not game over
	if (!isGameOver && sound.getStatus() == SoundSource::Status::Stopped)
	{
		sound.play();
	}
}

void EndlessGame::keyEvent(Event event)
{
	GameBase::keyEvent(event);
}

void EndlessGame::mouseEvent(RenderWindow& window, Event event)
{
	GameBase::mouseEvent(window, event);
}

void EndlessGame::render(RenderWindow& window)
{
	GameBase::render(window);


	text.setString("Score: " + to_string(score));
	text.setPosition(200, 500);
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
