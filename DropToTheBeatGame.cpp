#include "DropToTheBeatGame.h"


DropToTheBeatGame::DropToTheBeatGame(Controls_Settings& settings) : GameBase(settings)
{
}

DropToTheBeatGame::~DropToTheBeatGame()
{
}

void DropToTheBeatGame::tick(RenderWindow& window)
{
	GameBase::tick(window);
	if (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS + 200)
	{
		do
		{
			char beat[10];
			inFile.getline(beat, 10, '\r');
			nextBeatTimeMS = atoi(beat);
		} while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS); // if the time is too tight, skip to the next
		return;
	}
}

void DropToTheBeatGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);

	std::cout << "Drop to beat keyevent" << endl;

	if (key == settings.keyMap[static_cast<int> (Controls_Key::HARD_DROP)])
	{
		if (abs(sound.getPlayingOffset().asMilliseconds() - nextBeatTimeMS) < 200)
		{
			cout << "On beat" << endl;
		}
	}

}

void DropToTheBeatGame::render(RenderWindow& window)
{
	GameBase::render(window);
}
