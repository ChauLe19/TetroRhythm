#include "SprintGame.h"

SprintGame::SprintGame(StateManager &stateManager, Context context, std::string folderPath) : GameBase(stateManager, context, folderPath)
{
	timer = sf::Clock();
}

SprintGame::~SprintGame()
{
}

void SprintGame::tick(const float & dt, sf::RenderWindow& window)
{
	if (!isGameOver && linesCleared >= 40)
	{
		gameOver();
	}
}

void SprintGame::gameOver()
{
	GameBase::gameOver();
	if (linesCleared >= 40)
	{
		currSprintTime = timer.getElapsedTime().asMilliseconds();
		highscores->sprintTime = std::min(highscores->sprintTime, currSprintTime);
		GameSettings::getInstance()->saveHighscores();
	}
}

void SprintGame::restart()
{
	GameBase::restart();
	timer = sf::Clock();
}

void SprintGame::keyEvent(const float & dt, sf::Event event)
{
	GameBase::keyEvent(dt, event);
}

void SprintGame::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	GameBase::mouseEvent(dt, window, event);
}

void SprintGame::render(sf::RenderWindow& window)
{
	using namespace sf;
	using namespace std;
	GameBase::render(window);

	text.setFillColor(Color::White);
	text.setCharacterSize(70);
	text.setString("Lines left: " + to_string(40 - linesCleared));
	text.setPosition(100, 650);
	window.draw(text);

	if (isGameOver)
	{
		GameBase::renderGameOver(window);

		if (linesCleared >= 40) // success
		{
			Int32 tleft = highscores->sprintTime;
			bool isPB = currSprintTime == tleft;
			text.setFillColor(Color::Green);
			text.setCharacterSize(100);
			text.setString(isPB ? "Personal Best" : "Success");
			text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 300);
			window.draw(text);

			text.setFillColor(isPB ? Color::Green : Color::White);
			text.setCharacterSize(70);
			text.setString(getTimeFormat(currSprintTime));
			text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 200);
			window.draw(text);
		}
		else
		{
			text.setFillColor(Color::Red);
			text.setCharacterSize(100);
			text.setString("Failed");
			text.setPosition(1024 - text.getLocalBounds().width / 2, 576 - 250);
			window.draw(text);
		}
	}
	else
	{
		Int32 tleft = timer.getElapsedTime().asMilliseconds();
		text.setCharacterSize(70);
		text.setString(to_string(tleft / 1000/60) + ":"+to_string(tleft / 1000%60) + ":" + to_string((tleft % 1000)/10));
		text.setPosition(300, 550);
		window.draw(text);
	}
}
