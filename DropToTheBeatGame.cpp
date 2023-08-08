#include "DropToTheBeatGame.h"

DropToTheBeatGame::DropToTheBeatGame(StateManager &stateManager, string folderPath) : GameBase(stateManager, folderPath)
{
	this->clearBoardButton = new Button(Color::Black, 100, Color::White, "Clear", boardX - 200 - boardSquareSize, boardY + boardWidth * boardSquareSize - 200, 200, 200, Keyboard::Unknown);
}

DropToTheBeatGame::~DropToTheBeatGame()
{
	delete this->clearBoardButton;
}

void DropToTheBeatGame::tick(RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(window);

	// every secon passed, health + 1
	/*healthCounter++;
	if (healthCounter >= 60)
	{
		health = clamp(health  + 1, 0, 100);
		healthCounter = 0;
	}*/

	int tempTime = sound.getPlayingOffset().asMilliseconds();

	// if pressed in 400ms window, doesn't get "TOO LATE"
	// TOO LATE	-> health -= 10
	// MISS		-> health -= 1
	// ALMOST	-> health += 1
	// HIT		-> health += 2
	if (beatPressed)
	{
		if (abs(tempTime - nextBeatTimeMS) <= 100) // HIT
		{
			combo++;
			hitType = 2;
		}
		else if (abs(tempTime - nextBeatTimeMS) <= 250) // ALMOST
		{
			combo++;
			hitType = 1;

		}
		else // MISS
		{
			hitType = 0;
			combo = 0;
		}

		beatAccuracyCount[hitType]++;

		if (combo > maxCombo)
		{
			maxCombo = combo;
		}
		beatPressed = false;


		switch (hitType)
		{
			case 0:
				comboString = "MISS";
				health = clamp(health - 10, 0, 100);
			break;
			case 1:
				comboString = "ALMOST";
				health = clamp(health + 1, 0, 100);
			break;
			case 2:
				comboString = "HIT";
				health = clamp(health + 2, 0, 100);
			break;
			default:
				break;
		}

		// if next beat is in 200ms window, skip it or clear it
		if (abs(tempTime-nextBeatTimeMS) <= 250 && beatIt != beatsTime.end())
		{
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;
			if (beatIt != beatsTime.end())
				nextBeatTimeMS = *beatIt;
		}
	}
	else // too late, move to next beat
	{
		if (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS + 250 && beatIt != beatsTime.end())
		{
			combo = 0;
			comboString = "TOO LATE";
			beatAccuracyCount[0]++;
			health = clamp(health - 10, 0, 100);
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;
			nextBeatTimeMS = *beatIt;
		}
	}

	if (health <= 0)
	{
		gameOver();
		return;
	}

	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		finished = true;
		gameOver();
		ResultScreen *resultScreenPtr = new ResultScreen(stateManager, beatAccuracyCount, score, maxCombo);
		stateManager.addState(unique_ptr<StateScreen>(resultScreenPtr), false);
		reset();
		return;
	}
}

void DropToTheBeatGame::keyEvent(Event event)
{
	if (event.type != Event::KeyPressed) return;
	GameBase::keyEvent(event);

	// reset on top of the gamebase's reset
	if (event.key.code == Keyboard::Key::R)
	{
		restart();
	}
}

void DropToTheBeatGame::checkDropOnBeat()
{
}
void DropToTheBeatGame::mouseEvent(RenderWindow& window, Event event)
{
	if (finished) return;
	if (!isGameOver && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && 
		this->clearBoardButton->mouseInButton(window))
	{
		board.clearBoard();
		return;
	}
	else if (!isGameOver && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		beatPressed = true;
	}
	GameBase::mouseEvent(window, event);
}

void DropToTheBeatGame::restart()
{
	GameBase::restart();
	health = 100;
	healthCounter = 0;
	combo = 0;
	maxCombo = 0;
	beatPressed = false;
	beatAccuracyCount[0] = 0;
	beatAccuracyCount[1] = 0;
	beatAccuracyCount[2] = 0;
	finished = false;
}

void DropToTheBeatGame::render(RenderWindow& window)
{
	GameBase::render(window);
	GameBase::renderBeatSignal(window);


	RectangleShape healthRect;
	healthRect.setPosition(20, 40);
	healthRect.setSize(Vector2f(health * 5, 20));
	healthRect.setFillColor(Color::Yellow);
	healthRect.setOutlineColor(Color::Yellow);
	healthRect.setOutlineThickness(5);
	window.draw(healthRect);

	RectangleShape healthBar;
	healthBar.setPosition(20, 40);
	healthBar.setSize(Vector2f(500, 20));
	healthBar.setFillColor(Color::Transparent);
	healthBar.setOutlineColor(Color::White);
	healthBar.setOutlineThickness(5);
	window.draw(healthBar);

	text.setCharacterSize(50);
	text.setPosition(300, 600);
	text.setString("Combo");
	window.draw(text);
	text.setPosition(300, 650);
	text.setString(to_string(combo));
	window.draw(text);

	text.setFillColor(Color(255, 255, 255, 200));
	text.setString(comboString);
	text.setPosition(1024 - text.getLocalBounds().width / 2, boardY + boardSquareSize * 5 + 75 / 2);
	if (accuracyTimer > 0)
	{
		accuracyTimer--;
		window.draw(text);
	}
	this->clearBoardButton->render(window, text);

	/*if (bonus != 0 && clearTypeCounter > 0)
	{
		text.setPosition(700, 400);
		text.setString("+" + to_string(bonus));
		window.draw(text);
	}*/



	if (isGameOver && !finished)
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

