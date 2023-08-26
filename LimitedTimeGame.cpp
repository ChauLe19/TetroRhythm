#include "LimitedTimeGame.h"
#include "Utils.h"

//TODO: speed depends on the song speed. the song speed up after every round
LimitedTimeGame::LimitedTimeGame(StateManager& stateManager, string folderPath) : GameBase(stateManager, folderPath)
{
	clock = Clock();
}

LimitedTimeGame::~LimitedTimeGame()
{
}

void LimitedTimeGame::tick(const float & dt, RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(dt, window);
	frameCount++;
	// restart song if not game over
	if (!isGameOver && sound.getStatus() == SoundSource::Status::Stopped)
	{
		sound.play();
	}

	if (clock.getElapsedTime().asSeconds() >= 120)
	{
		gameOver();
	}
}

void LimitedTimeGame::keyEvent(const float & dt, Event event)
{
	if (event.type != Event::KeyPressed) return;
	GameBase::keyEvent(dt, event);
	if (event.key.code == Keyboard::R)
	{
		clock = Clock();
	}
}

void LimitedTimeGame::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	if (isGameOver && Mouse::isButtonPressed(Mouse::Left) && mouseInBox(window, 1024 - 150, 576 - 60 - 20, 300, 60)) // RESTART button
	{
		clock = Clock();
	}
	GameBase::mouseEvent(dt, window, event);
}

void LimitedTimeGame::render(RenderWindow& window)
{
	GameBase::render(window);

	Int32 tleft = 120000-clock.getElapsedTime().asMilliseconds();
	text.setString("Time left: " + to_string(tleft / 1000/60) + ":"+to_string(tleft / 1000%60) + ":" + to_string(tleft % 1000));
	text.setPosition(200, 600);
	window.draw(text);

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
