#include "EndlessGame.h"

//TODO: speed depends on the song speed. the song speed up after every round
EndlessGame::EndlessGame(StateManager &stateManager, Context context, std::string folderPath) : GameBase(stateManager, context, folderPath)
{
}

EndlessGame::~EndlessGame()
{
}

void EndlessGame::tick(const float & dt, sf::RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(dt, window);
	frameCount++;
	// restart song if not game over
	if (!isGameOver && sound.getStatus() == sf::SoundSource::Status::Stopped)
	{
		sound.play();
	}
}

void EndlessGame::gameOver()
{
	GameBase::gameOver();
	highscores->endless = std::max(highscores->endless, score);
	GameSettings::getInstance()->saveHighscores();
}

void EndlessGame::keyEvent(const float & dt, sf::Event event)
{
	GameBase::keyEvent(dt, event);
}

void EndlessGame::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	GameBase::mouseEvent(dt, window, event);
	if (isGameOver && !hsSaved)
	{
		hsSaved = true;
	}
}

void EndlessGame::render(sf::RenderWindow& window)
{
	using namespace std;
	GameBase::render(window);

	if (isGameOver)
	{
		GameBase::renderGameOver(window);

		text.setCharacterSize(80);
		text.setFillColor(sf::Color::White);
		text.setString(to_string(score));
		text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 250);
		window.draw(text);
	}
}
