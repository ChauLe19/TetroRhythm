#include "LimitedTimeGame.h"
#include "Utils.h"

//TODO: speed depends on the song speed. the song speed up after every round
LimitedTimeGame::LimitedTimeGame(StateManager& stateManager, std::string folderPath) : GameBase(stateManager, folderPath)
{
	clock = sf::Clock();
}

LimitedTimeGame::~LimitedTimeGame()
{
}

void LimitedTimeGame::tick(const float & dt, sf::RenderWindow& window)
{
	using namespace sf;
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
		sound.stop();
		isGameOver = true;
	}
}

void LimitedTimeGame::gameOver()
{
	GameBase::gameOver();
	highscores->limit = std::max(highscores->limit, score);
	GameSettings::getInstance()->saveHighscores();
}

void LimitedTimeGame::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
	if (event.type != Event::KeyPressed && event.type != Event::KeyReleased) return;
	GameBase::keyEvent(dt, event);
	if (event.key.code == Keyboard::R)
	{
		clock = Clock();
	}
}

void LimitedTimeGame::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	if (isGameOver && Mouse::isButtonPressed(Mouse::Left) && mouseInBox(window, 1024 - 150, 576 - 60 - 20, 300, 60)) // RESTART button
	{
		clock = Clock();
	}
	GameBase::mouseEvent(dt, window, event);
}

void LimitedTimeGame::render(sf::RenderWindow& window)
{
	using namespace sf;
	using namespace std;
	GameBase::render(window);

	Int32 tleft = 120000-clock.getElapsedTime().asMilliseconds();
	text.setCharacterSize(50);
	text.setString("Time left ");
	text.setPosition(300, 500);
	window.draw(text);
	text.setCharacterSize(70);
	text.setString(getTimeFormat(tleft));
	text.setPosition(300, 550);
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
