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

	// must play before setPlayingOffset
	sound.play();
	sound.pause();
	sound.setPlayingOffset(milliseconds(0));
	cursorRelToMusicMS = sound.getPlayingOffset().asMilliseconds();
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


	// must play before setPlayingOffset
	sound.play();
	sound.pause();
	sound.setPlayingOffset(milliseconds(0));
	cursorRelToMusicMS = sound.getPlayingOffset().asMilliseconds();
}

BeatMapEditor::~BeatMapEditor()
{
}

void BeatMapEditor::save()
{
	outFile.open(textFilePath, ios::out);
	list<int>::iterator it = beatsTime.begin();

	while (it != beatsTime.end())
	{
		outFile << *it << '\r';
		it++;
	}
	outFile.close();
}

void BeatMapEditor::tick(RenderWindow& window)
{
	if (sound.getStatus() == Music::Status::Stopped)
	{
		sound.play();
		sound.pause();
		sound.setPlayingOffset(milliseconds(musicDurationMS));
	}
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

	wholeAudioSlider.setSize(Vector2f(sliderLength, sliderHeight));
	wholeAudioSlider.setFillColor(Color(0, 0, 0, 0));
	wholeAudioSlider.setOutlineColor(Color::White);
	wholeAudioSlider.setOutlineThickness(5);
	wholeAudioSlider.setPosition(24, 1000);
	window.draw(wholeAudioSlider);

	wholeAudioCursor.setSize(Vector2f(10, sliderHeight));
	wholeAudioCursor.setFillColor(Color::Yellow);
	wholeAudioCursor.setOutlineColor(Color::Yellow);
	wholeAudioCursor.setPosition(24 - 5 + sliderLength * cursorRelToMusicMS / musicDurationMS, 1000);
	window.draw(wholeAudioCursor);


	partAudioSlider.setSize(Vector2f(sliderLength, sliderHeight));
	partAudioSlider.setOutlineColor(Color::White);
	partAudioSlider.setOutlineThickness(5);
	partAudioSlider.setFillColor(Color(0, 0, 0, 0));
	partAudioSlider.setPosition(24, 50);
	window.draw(partAudioSlider);


	partAudioCursor.setSize(Vector2f(10, sliderHeight));
	partAudioCursor.setFillColor(Color::Yellow);
	partAudioCursor.setOutlineColor(Color::Yellow);
	partAudioCursor.setPosition(24 - 5 + sliderLength / 2, 50); // middle of slider
	window.draw(partAudioCursor);


	list<int>::iterator it = beatsTime.begin();
	while (it != beatsTime.end())
	{
		RectangleShape beat;
		beat.setSize(Vector2f(4, sliderHeight / 2));
		beat.setFillColor(Color::Green);
		beat.setPosition(24 - 2 + sliderLength * (*it) / musicDurationMS, 1000 + sliderHeight / 2);
		window.draw(beat);


		if (cursorRelToMusicMS >= *it - 2500 && cursorRelToMusicMS <= *it + 2500)
		{
			RectangleShape beatInPartSlider;
			beatInPartSlider.setSize(Vector2f(4, sliderHeight / 2));
			beatInPartSlider.setFillColor(Color::Green);
			beatInPartSlider.setPosition(24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - *it) / 2500, 50 + sliderHeight / 2);
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
		save();
		state = State::MENU;
		break;
	case Keyboard::Key::Space:
		if (sound.getPlayingOffset().asMilliseconds() == musicDurationMS)
		{
			//basically restart if at the end
			sound.setPlayingOffset(milliseconds(0));
			sound.play();
		}
		else if (sound.getStatus() != Music::Status::Playing)
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
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	return (mouseViewPos.x >= x && mouseViewPos.x <= x + width
		&& mouseViewPos.y >= y && mouseViewPos.y <= y + height);
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
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	if (firstPressed && mouseInBox(window, 24 - 5 + sliderLength * cursorRelToMusicMS / musicDurationMS, 1000, 10, sliderHeight))
	{
		firstPressed = false;
		cursorSelected = true;
		cursorRelToMusicMS = (mouseViewPos.x - 24 + 5) * musicDurationMS / sliderLength;
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
		cursorRelToMusicMS = (mouseViewPos.x - 24 + 5) * musicDurationMS / sliderLength;
		cursorRelToMusicMS = clamp(cursorRelToMusicMS, 0, musicDurationMS);
		sound.setPlayingOffset(milliseconds(cursorRelToMusicMS));
	}
	//cout << "x:" << 24 - 10 + sliderLength * cursorRelToMusicMS / musicDurationMS << endl;
	//cout << "mouse x: " << mouseViewPos.x << endl;
}



