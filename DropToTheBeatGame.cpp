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

void DropToTheBeatGame::tick(RenderWindow& window)
{
	GameBase::tick(window);

	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		gameOver();
	}

	if (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS + 200)
	{
		if (!beatPressed)
		{
			combo = 0;
		}
		while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS && beatIt != beatsTime.end())
		{
			beatIt++;
			if (beatIt != beatsTime.end())
				nextBeatTimeMS = *beatIt;
			beatPressed = false;
		}
		return;
	}
}

void DropToTheBeatGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);

	if (key == keybinds["HARD_DROP"])
	{
		if (abs(sound.getPlayingOffset().asMilliseconds() - nextBeatTimeMS) < 200)
		{
			combo++;
			beatPressed = true;
		}
		else
		{
			beatPressed = true;
			combo = 0;
		}
	}

}

void DropToTheBeatGame::render(RenderWindow& window)
{
	GameBase::render(window);
	GameBase::renderBeatSignal(window);
	text.setCharacterSize(30);
	text.setPosition(700, 500);
	text.setString("Combo");
	window.draw(text);
	text.setPosition(700, 550);
	text.setString(to_string(combo));
	window.draw(text);
}
