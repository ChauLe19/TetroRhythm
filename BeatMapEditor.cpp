#include "BeatMapEditor.h"

BeatMapEditor::BeatMapEditor(string audioFilePath)
{
	this->audioFilePath = audioFilePath;
	this->textFilePath = "output.txt"; // change to text file file with audio file path
	if (!buffer.loadFromFile(audioFilePath))
	{
		cerr << "Unable to open file " + audioFilePath << endl;;
	}
	sound.setBuffer(buffer);

	musicDurationMS = buffer.getDuration().asMilliseconds();
	cursor = 0;
}

BeatMapEditor::BeatMapEditor(string audioFilePath, string textFilePath)
{
	this->audioFilePath = audioFilePath;
	this->textFilePath = textFilePath;
	if (!buffer.loadFromFile(audioFilePath))
	{
		cerr << "Unable to open file " + audioFilePath << endl;;
	}
	sound.setBuffer(buffer);

	musicDurationMS = buffer.getDuration().asMilliseconds();
	cursor = 0;

	inFile.open(textFilePath);
	if (!inFile)
	{
		cerr << "Unable to open file " + textFilePath << endl;;
	}
	else
	{
		char beat[10];
		while (inFile.getline(beat, 10, '\r'))
		{
			beatsTime.push_back(atoi(beat));
		}
	}
	beatIt = beatsTime.begin();

}

BeatMapEditor::~BeatMapEditor()
{
	inFile.close();
	outFile.open(textFilePath);
	list<int>::iterator it = beatsTime.begin();

	while (it != beatsTime.end())
	{
		outFile << *it << endl;
		it++;
	}
	outFile.close();
}

void BeatMapEditor::tick(RenderWindow& window)
{
	cursorRelToMusicMS = sound.getPlayingOffset().asMilliseconds();
}

void BeatMapEditor::render(RenderWindow& window)
{
	if (sound.getStatus() != Music::Status::Playing)
	{
		CircleShape playButton(20, 3);
		playButton.setFillColor(Color::White);
		playButton.setPosition(300, 300);
		playButton.rotate(90);
		window.draw(playButton);
	}
	else
	{
		RectangleShape left;
		left.setSize(Vector2f(10, 40));
		left.setFillColor(Color::White);
		left.setPosition(300, 300);
		
		RectangleShape right;
		right.setSize(Vector2f(10, 40));
		right.setFillColor(Color::White);
		right.setPosition(320, 300);

		window.draw(left);
		window.draw(right);
	}

	RectangleShape wholeAudioSlider; // a slider of the whole audio file
	RectangleShape wholeAudioCursor; // cursor for whole audio slider
	RectangleShape partAudioSlider; // a slider show only 5 sec part of the audio at the cursor
	RectangleShape partAudioCursor; // cursor for part audio slider

	wholeAudioSlider.setSize(Vector2f(500, 50));
	wholeAudioSlider.setFillColor(Color(0, 0, 0, 0));
	wholeAudioSlider.setOutlineColor(Color::White);
	wholeAudioSlider.setOutlineThickness(5);
	wholeAudioSlider.setPosition(50, 50);
	window.draw(wholeAudioSlider);

	wholeAudioCursor.setSize(Vector2f(10, 50));
	wholeAudioCursor.setFillColor(Color::Yellow);
	wholeAudioCursor.setOutlineColor(Color::Yellow);
	wholeAudioCursor.setPosition(50 - 5 + 500 * cursorRelToMusicMS / musicDurationMS, 50);
	window.draw(wholeAudioCursor);


	partAudioSlider.setSize(Vector2f(500, 50));
	partAudioSlider.setOutlineColor(Color::White);
	partAudioSlider.setOutlineThickness(5);
	partAudioSlider.setFillColor(Color(0, 0, 0, 0));
	partAudioSlider.setPosition(50, 150);
	window.draw(partAudioSlider);


	partAudioCursor.setSize(Vector2f(10, 50));
	partAudioCursor.setFillColor(Color::Yellow);
	partAudioCursor.setOutlineColor(Color::Yellow);
	partAudioCursor.setPosition(50 - 5 + 250, 150); // middle of slider
	window.draw(partAudioCursor);


	list<int>::iterator it = beatsTime.begin();
	while (it != beatsTime.end())
	{
		RectangleShape beat;
		beat.setSize(Vector2f(4, 25));
		beat.setFillColor(Color::Green);
		beat.setPosition(50 - 2 + 500 * (*it) / musicDurationMS, 50 + 25);
		window.draw(beat);


		if (cursorRelToMusicMS >= *it - 2500 && cursorRelToMusicMS <= *it + 2500)
		{
			RectangleShape beatInPartSlider;
			beatInPartSlider.setSize(Vector2f(4, 25));
			beatInPartSlider.setFillColor(Color::Green);
			beatInPartSlider.setPosition(50 - 2 + 250 - 250 * (cursorRelToMusicMS - *it) / 2500, 150 + 25);
			window.draw(beatInPartSlider);
		}


		it++;


	}

}

void BeatMapEditor::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Escape:
		state = State::MENU;
		break;
	case Keyboard::Key::Space:
		if (sound.getStatus() != Music::Status::Playing)
		{
			sound.play();
		}
		else
		{
			sound.pause();
		}
	}
}

bool mouseInBox(RenderWindow& window, int x, int y, int width, int height)
{
	return (Mouse::getPosition(window).x > x && Mouse::getPosition(window).x < x + width
		&& Mouse::getPosition(window).y > y && Mouse::getPosition(window).y < y + height);
}
int clamp(int var, int min, int max)
{
	if (var < min)
	{
		return min;
	}
	else if (var > max)
	{
		return max;
	}
	return var;
}
void BeatMapEditor::mouseEvent(RenderWindow& window)
{
	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		firstPressed = true;
		cursorSelected = false;
		return;
	}
	if (firstPressed && mouseInBox(window, 50 - 5 + 500 * cursorRelToMusicMS / musicDurationMS, 50, 10, 50))
	{
		firstPressed = false;
		cursorSelected = true;
		cursorRelToMusicMS = (Mouse::getPosition(window).x - 50 + 5) * musicDurationMS / 500;
		cursorRelToMusicMS = clamp(cursorRelToMusicMS, 0, musicDurationMS);
		sound.setPlayingOffset(milliseconds(cursorRelToMusicMS));
	}
	else if (firstPressed)
	{
		firstPressed = false;
		cursorSelected = false;
	}
	else if (!firstPressed && cursorSelected)
	{
		cursorRelToMusicMS = (Mouse::getPosition(window).x - 50 + 5) * musicDurationMS / 500;
		cursorRelToMusicMS = clamp(cursorRelToMusicMS, 0, musicDurationMS);
		sound.setPlayingOffset(milliseconds(cursorRelToMusicMS));
	}
}



