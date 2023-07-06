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

	int tempTime = sound.getPlayingOffset().asMilliseconds();

	// if pressed in 400ms window, doesn't get "TOO LATE"
	if (beatPressed)
	{
		beatPressed = false;

		if (hitType == 0)
		{
			comboString = "MISS";
			if (!createGarbageLine(rand() % boardWidth)) gameOver();

		}
		else if (hitType == 1)
		{
			comboString = "ALMOST";
		}
		else if (hitType == 2)
		{
			comboString = "HIT";
		}

		// if next beat is in 200ms window, skip it or clear it
		if (tempTime <= nextBeatTimeMS + 200 && beatIt != beatsTime.end())
		{
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;
			if (beatIt != beatsTime.end())
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
			prevBeatTimeMS = nextBeatTimeMS;
			beatIt++;
			if (beatIt != beatsTime.end())
				nextBeatTimeMS = *beatIt;
			accuracyTimer = 60;
			if (!createGarbageLine(rand() % boardWidth)) gameOver();
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
		combo = 0;
		beatPressed = false;
		beatAccuracyCount[0] = 0;
		beatAccuracyCount[1] = 0;
		beatAccuracyCount[2] = 0;
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

	text.setCharacterSize(50);
	text.setPosition(680, 600);
	text.setString("Combo");
	window.draw(text);
	text.setPosition(680, 650);
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

