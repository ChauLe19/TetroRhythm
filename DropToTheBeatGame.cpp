#include "DropToTheBeatGame.h"

DropToTheBeatGame::DropToTheBeatGame(Controls_Settings& settings) : GameBase(settings)
{
}
DropToTheBeatGame::DropToTheBeatGame(Controls_Settings& settings, string folderPath) : GameBase(settings, folderPath)
{
}

DropToTheBeatGame::~DropToTheBeatGame()
{
}


void DropToTheBeatGame::tick(State& state, RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(state, window);

	// it's triggered only when the sound stops on its own
	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		finished = true;
		gameOver();
		state = State::GAMEOVER;
		return;
	}
	// every secon passed, health + 1
		/*healthCounter++;
		if (healthCounter >= 60)
		{
			health = clamp(health  + 1, 0, 100);
			healthCounter = 0;
		}*/

	if (health <= 0)
	{
		gameOver();
		return;
	}

	int tempTime = sound.getPlayingOffset().asMilliseconds();

	// if pressed in 400ms window, doesn't get "TOO LATE"
	// TOO LATE	-> health -= 10
	// MISS		-> health -= 1
	// ALMOST	-> health += 1
	// HIT		-> health += 2
	if (beatPressed)
	{
		beatPressed = false;

		if (hitType != 0 && (recentClearType == ClearType::TSPIN_DOUBLE || recentClearType == ClearType::TSPIN_MINI_DOUBLE
			|| recentClearType == ClearType::B2B_TSPIN_DOUBLE || recentClearType == ClearType::B2B_TSPIN_MINI_DOUBLE
			|| recentClearType == ClearType::TSPIN_SINGLE || recentClearType == ClearType::TSPIN_MINI_SINGLE
			|| recentClearType == ClearType::B2B_TSPIN_SINGLE || recentClearType == ClearType::B2B_TSPIN_SINGLE
			|| recentClearType == ClearType::TSPIN_TRIPLE || recentClearType == ClearType::B2B_TSPIN_TRIPLE))
		{
			health = clamp(health + 10, 0, 100);
		}

		if (hitType == 0)
		{
			comboString = "MISS";
			health = clamp(health - 15, 0, 100);
		}
		else if (hitType == 1)
		{
			comboString = "ALMOST";
			health = clamp(health + 1, 0, 100);
		}
		else if (hitType == 2)
		{
			comboString = "HIT";
			health = clamp(health + 2, 0, 100);
		}

		// early 200ms, that beat is gone
		if (tempTime >= nextBeatTimeMS - 200 && beatIt != beatsTime.end())
		{
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;
			nextBeatTimeMS = *beatIt;
		}
		accuracyTimer = 60;
	}
	else // too late, move to next beat
	{
		if (tempTime > nextBeatTimeMS + 200 && beatIt != beatsTime.end())
		{
			combo = 0;
			comboString = "LATE";
			beatAccuracyCount[0]++;
			health = clamp(health - 15, 0, 100);
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;

			nextBeatTimeMS = *beatIt;
			accuracyTimer = 60;
		}
	}
}

void DropToTheBeatGame::tick(State& state, RenderWindow& window, ResultScreen*& resultScreenPtr)
{
	tick(state, window);
	if (finished)
	{
		state = State::GAMEOVER;
		resultScreenPtr = new ResultScreen(beatAccuracyCount, score, maxCombo);
		return;
	}
	healthCounter++;
	if (healthCounter >= 60)
	{
		health = clamp(health + 1, 0, 100);
		healthCounter = 0;
	}
	if (health <= 0)
	{
		gameOver();
	}
	if (beatPressed)
	{
		beatPressed = false;
		if (hitType == 0)
		{
			comboString = "MISS";
		}
		else if (hitType == 1)
		{
			comboString = "ALMOST";
			health = std::clamp(health + 1, 0, 100);
		}
		else if (hitType == 2)
		{
			comboString = "HIT";
			health = std::clamp(health + 2, 0, 100);
		}
		while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS - 100 && beatIt != beatsTime.end())
		{
			beatIt++;
			if (beatIt != beatsTime.end())
				nextBeatTimeMS = *beatIt;
			beatPressed = false;
		}

	}
	else
	{
		if (sound.getPlayingOffset().asMilliseconds() >= nextBeatTimeMS + 100 && beatIt != beatsTime.end())
		{
			combo = 0;
			comboString = "TOO LATE";
			health = std::clamp(health - 10, 0, 100);
			while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS && beatIt != beatsTime.end())
			{
				beatIt++;
				if (beatIt != beatsTime.end())
					nextBeatTimeMS = *beatIt;
				beatPressed = false;
			}
		}
	}
}

void DropToTheBeatGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
	int tempTime = sound.getPlayingOffset().asMilliseconds();
	//if (key == keybinds["HARD_DROP"] || key == keybinds["ROTATE_CW"] || key == keybinds["ROTATE_CCW"])
	if (key == keybinds["HARD_DROP"])
	{
		if (abs(tempTime - nextBeatTimeMS) <= 100) // HIT
		{
			combo++;
			hitType = 2;
			beatPressed = true;
		}
		else if (abs(tempTime - nextBeatTimeMS) <= 200) // ALMOST
		{
			combo++;
			hitType = 1;
			beatPressed = true;

		}
		else // MISS
		{
			hitType = 0;
			beatPressed = true;
			combo = 0;
		}

		beatAccuracyCount[hitType]++;

		// already added clear type in GameBase, now add bonus to it
		// if combo < 1, no combo added
		// if combo >=1, bonus = (combo)/100 * (clear score + hard drop score)
		// combo is capped at 100	-> which means max bonus = clear score
		bonus = clamp(combo, 0, 100) * convertClearTypeToScores(recentClearType) / 100;
		score += bonus;

		if (combo > maxCombo)
		{
			maxCombo = combo;
		}
	}

	// reset on top of the gamebase's reset
	if (key == Keyboard::Key::R)
	{
		restart();
	}
}

void DropToTheBeatGame::mouseEvent(State& state, RenderWindow& window)
{
	if (!isGameOver || finished) return;
	GameBase::mouseEvent(state, window);
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
	text.setPosition(1024 - text.getLocalBounds().width / 2, boardY + squareSize * 5 + 75 / 2);
	if (accuracyTimer > 0)
	{
		accuracyTimer--;
		window.draw(text);
	}

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

