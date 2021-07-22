#include "DropToTheBeatGame.h"

void DropToTheBeatGame::tick(RenderWindow& window, int& frameCount)
{
	if (isGameOver) return;
	if (frameCount >= 48)
	{
		currentPiecePtr->move(Moving_Direction::DOWN_DIR, board);
		frameCount = 0;
	}
	if (sound.getStatus() == SoundSource::Status::Stopped)
	{
		gameOver();
	}
	

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
