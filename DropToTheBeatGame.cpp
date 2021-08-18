#include "DropToTheBeatGame.h"

//TODO: If miss 1 beat, 1 garbage line
DropToTheBeatGame::DropToTheBeatGame(Controls_Settings& settings) : GameBase(settings)
{
}
DropToTheBeatGame::DropToTheBeatGame(Controls_Settings& settings, string folderPath) : GameBase(settings, folderPath)
{
}

DropToTheBeatGame::~DropToTheBeatGame()
{
}

//TODO: if TSD or TST, health += 10 || 15
void DropToTheBeatGame::tick(RenderWindow& window)
{
	if (isGameOver) return;
	GameBase::tick(window);

	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		gameOver();
		return;
	}
	healthCounter++;
	if (healthCounter >= 60)
	{
		health = clamp(health  + 1, 0, 100);
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
			health = clamp(health + 1, 0, 100);
		}
		else if (hitType == 2)
		{
			comboString = "HIT";
			health = clamp(health + 2, 0, 100);
		}
		while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS-100 && beatIt != beatsTime.end())
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
			health = clamp(health - 10, 0, 100);
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

	//if (key == keybinds["HARD_DROP"] || key == keybinds["ROTATE_CW"] || key == keybinds["ROTATE_CCW"])
	if (key == keybinds["HARD_DROP"])
	{
		if (abs(sound.getPlayingOffset().asMilliseconds() - nextBeatTimeMS) <= 50)
		{
			combo++;
			hitType = 2;
			beatPressed = true;
		}
		else if (abs(sound.getPlayingOffset().asMilliseconds() - nextBeatTimeMS) <= 100)
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
			health = clamp(health - 10, 0, 100);

		}
	}

	// reset on top of the gamebase's reset
	if (key == Keyboard::Key::R)
	{
		health = 100;
		healthCounter = 0;
		combo = 0;
		beatPressed = false;
	}
}

void DropToTheBeatGame::render(RenderWindow& window)
{
	GameBase::render(window);
	GameBase::renderBeatSignal(window);
	text.setCharacterSize(30);
	text.setPosition(680, 500);
	text.setString("Combo");
	window.draw(text);
	text.setPosition(680, 550);
	text.setString(to_string(combo));
	window.draw(text);
	
	text.setPosition(680, 600);
	text.setString(comboString);
	window.draw(text);


	RectangleShape healthRect;
	healthRect.setPosition(20, 40);
	healthRect.setSize(Vector2f(health * 5,20));
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


}
