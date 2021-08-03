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

	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		gameOver();
	}

	if (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS + 200)
	{
		while (sound.getPlayingOffset().asMilliseconds() > nextBeatTimeMS && beatIt != beatsTime.end());
		{
			beatIt++;
			nextBeatTimeMS = *beatIt;
		}
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
	GameBase::renderBeatSignal(window);
}
