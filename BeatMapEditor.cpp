#include "BeatMapEditor.h"

BeatMapEditor::BeatMapEditor(string folderPath)
{
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);


	fs::path audioPath = folderPath;
	audioPath.append(audioPath.filename().string() + ".ogg");
	cout << "Beat map editor" << endl;
	if (!fs::exists(audioPath))
	{
		audioPath = audioPath.parent_path();
		audioPath.append(audioPath.filename().string() + ".wav");
		if (!fs::exists(audioPath))
			cerr << "Audio file doesn't exist." << endl;
	}

	fs::path txtPath = folderPath;
	txtPath.append(txtPath.filename().string() + ".txt");

	if (!fs::exists(txtPath))
		cerr << "Text file doesn't exist." << endl;


	this->audioFilePath = fs::absolute(audioPath).string();
	this->textFilePath = fs::absolute(txtPath).string(); // change to text file file with audio file path
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
	text.setFillColor(Color::White);
	text.setPosition(20, 20);
	text.setCharacterSize(20);
	text.setString("Drag the bottom cursor to navigate along the beats. Hover your mouse over green tick(s) while holding right click to erase them. Press B or right click the center circle to place beat. Spacebar to play/pause.");
	window.draw(text);

	if (sound.getStatus() != Music::Status::Playing)
	{
		CircleShape playButton(40, 3);
		playButton.setFillColor(Color::White);
		playButton.setPosition(1060, 900);
		playButton.rotate(90);
		window.draw(playButton);
	}
	else
	{
		RectangleShape left;
		left.setSize(Vector2f(15, 60));
		left.setFillColor(Color::White);
		left.setPosition(1000, 900);

		RectangleShape right;
		right.setSize(Vector2f(15, 60));
		right.setFillColor(Color::White);
		right.setPosition(1040, 900);

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


	CircleShape beatButton;
	beatButton.setRadius(250);
	beatButton.setPosition(1024 - 250, 576 - 250);
	beatButton.setOutlineColor(Color::White);

	window.draw(beatButton);
}

void BeatMapEditor::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Escape:
		save();
		sound.stop();
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
		break;
	case Keyboard::Key::B:
		addCursorToBeatList();
		break;
	}
}

bool mouseInBox(RenderWindow& window, int x, int y, int width, int height)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	return (mouseViewPos.x >= x && mouseViewPos.x <= x + width
		&& mouseViewPos.y >= y && mouseViewPos.y <= y + height);
}
bool mouseInCircle(RenderWindow& window, int x, int y, int r)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	return (mouseViewPos.x - x) * (mouseViewPos.x - x) + (mouseViewPos.y - y) * (mouseViewPos.y - y) <= r * r;
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

void BeatMapEditor::addCursorToBeatList()
{

	list<int>::iterator temp = beatsTime.begin();
	int prev = 0;
	while (temp != beatsTime.end() && *temp < cursorRelToMusicMS)
	{
		prev = *temp;
		temp++;
	}

	if (temp == beatsTime.end())
	{
		beatsTime.push_back(cursorRelToMusicMS);
		return;
	}
	// reject beat that is too close to already existed
	if (prev + 100 <= cursorRelToMusicMS && *temp - 100 >= cursorRelToMusicMS)
	{
		beatsTime.insert(temp, cursorRelToMusicMS);
	}
}

void BeatMapEditor::mouseEvent(RenderWindow& window)
{

	if (Mouse::isButtonPressed(Mouse::Right))
	{
		list<int>::iterator it = beatsTime.begin();
		while (it != beatsTime.end())
		{
			// for the part slider only
			if (cursorRelToMusicMS >= *it - 2500 && cursorRelToMusicMS <= *it + 2500)
			{
				// erase beat that mouse if over when right mouse is pressed	
				if (mouseInBox(window, 24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - *it) / 2500, 50 + sliderHeight / 2, 4, sliderHeight / 2))
				{
					beatsTime.erase(it);
					break;
				}
			}
			it++;
		}
	}

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
	else if (firstPressed && mouseInCircle(window, 1024, 576, 250))
	{
		firstPressed = false;

		addCursorToBeatList();
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



