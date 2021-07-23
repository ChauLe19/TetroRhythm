#include "DropToTheBeatGame.h"

DropToTheBeatGame::DropToTheBeatGame(array<Keyboard::Key, 8>& keyMap) : GameBase(keyMap)
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

void DropToTheBeatGame::dropOnBeat()
{
	cout << "press at:" << sound.getPlayingOffset().asMilliseconds() << "\tplaying at:"<< nextBeatTimeMS << endl;
	if (abs(sound.getPlayingOffset().asMilliseconds() - nextBeatTimeMS) < 200)
	{
		cout << "On beat" << endl;
	}
}

void DropToTheBeatGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
	std::cout << "Drop to beat keyevent" << endl;
}
