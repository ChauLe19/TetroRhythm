#include "BeatMapEditor.h"
#include "Menu.h"

BeatMapEditor::BeatMapEditor(StateManager &stateManager, string folderPath) : StateScreen(stateManager)
{
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);
	speedButton025 = new Button(Color::Black, 35, Color::White, "x0.25\n(Press 2)", 1500, 300, 100, 70, Keyboard::Key::Num2);
	speedButton050 = new Button(Color::Black, 35, Color::White, "x0.50\n(Press 5)", 1650, 300, 100, 70, Keyboard::Key::Num5);
	speedButton100 = new Button(Color::Black, 35, Color::White, "x1\n(Press 1)", 1800, 300, 100, 70, Keyboard::Key::Num1);


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
		if (inFile.getline(beat, 10, '\r')) // read bpm
		{
			char temp[6] = { 0 };

			std::copy(beat + 10 - 6, beat + 10, temp);

			bpm = atoi(temp);
			mspb = std::round(60 * 1000 / bpm);
			std::cout << bpm << std::endl;
		}
		else
		{
			breakfastquay::MiniBPM bpmDetector(buffer.getSampleRate());

			int sampleCount = buffer.getSampleCount();
			auto samples = buffer.getSamples();
			float* fSamples = new float[buffer.getSampleCount()];
			for (int i = 0; i < sampleCount; i++)
			{
				fSamples[i] = static_cast<float>(samples[i]);
			}
			bpm = std::round(bpmDetector.estimateTempoOfSamples(fSamples, buffer.getSampleCount()));
			mspb = 60 * 1000 / bpm;
			std::cout << bpm << std::endl;

		}

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

BeatMapEditor::BeatMapEditor(StateManager &stateManager, string audioFilePath, string textFilePath) : StateScreen(stateManager)

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
	delete speedButton025;
	delete speedButton050;
	delete speedButton100;
}

void BeatMapEditor::save()
{
	outFile.open(textFilePath, ios::out);
	outFile << "bpm " << bpm << '\r';
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
	text.setPosition(20, 10);
	text.setCharacterSize(30);
	text.setString("Drag the bottom cursor to navigate along the beats. Hover your mouse over green tick(s) while holding right click to erase them. Press B or right click the center circle to place beat. Spacebar to play/pause.");
	window.draw(text);

	speedButton025->render(window, text);
	speedButton050->render(window, text);
	speedButton100->render(window, text);

	if (sound.getStatus() != Music::Status::Playing) // draw playing status
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


	list<int>::iterator it = beatsTime.begin(); // draw beats
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
			beatInPartSlider.setSize(Vector2f(10, sliderHeight * 2 / 3));
			beatInPartSlider.setFillColor(Color::Green);
			beatInPartSlider.setPosition(24 - 10 / 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - *it) / 2500, 50 + sliderHeight / 3);
			window.draw(beatInPartSlider);
		}


		it++;
	}


	// render minor notes
	for (int i = std::ceil((float)(cursorRelToMusicMS - 2500) / ((float)mspb / 4)); i <= std::floor((float)(cursorRelToMusicMS + 2500) / ((float)mspb / 4)); i++)
	{
		RectangleShape beatInPartSlider;
		beatInPartSlider.setSize(Vector2f(4, sliderHeight / 4));
		beatInPartSlider.setFillColor(Color::Blue);
		int t = i * (float)mspb / 4;
		beatInPartSlider.setPosition(24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - t) / 2500, 50 + sliderHeight * 3 / 8);
		window.draw(beatInPartSlider);
	}

	//render major notes
	for (int i = std::ceil((float)(cursorRelToMusicMS - 2500) / (mspb)); i <= std::floor((float)(cursorRelToMusicMS + 2500) / (mspb)); i++)
	{
		RectangleShape beatInPartSlider;
		beatInPartSlider.setSize(Vector2f(4, sliderHeight / 4));
		beatInPartSlider.setFillColor(Color(211, 211, 211));
		int t = i * mspb;
		beatInPartSlider.setPosition(24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - t) / 2500, 50 + sliderHeight * 3 / 8);
		window.draw(beatInPartSlider);
	}



	CircleShape beatButton;
	beatButton.setRadius(250);
	beatButton.setPosition(1024 - 250, 576 - 250);
	beatButton.setOutlineColor(Color::White);

	window.draw(beatButton);
}

void BeatMapEditor::keyEvent(Event event)
{
	if (event.type != Event::KeyPressed) return;
	Keyboard::Key key = event.key.code;
	switch (key)
	{
	case Keyboard::Key::Escape:
		save();
		sound.stop();
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		break;
	case Keyboard::Key::Num2:
		sound.setPitch(0.25);
		break;
	case Keyboard::Key::Num5:
		sound.setPitch(0.5);
		break;
	case Keyboard::Key::Num1:
		sound.setPitch(1);
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

void BeatMapEditor::addCursorToBeatList()
{
	int nearestBeat = std::round((float)(cursorRelToMusicMS) / ((float)mspb / 4));
	nearestBeat = nearestBeat * ((float)mspb / 4);
	list<int>::iterator temp = beatsTime.begin();
	int prev = 0;
	while (temp != beatsTime.end() && *temp < nearestBeat)
	{
		prev = *temp;
		temp++;
	}

	if (temp == beatsTime.end())
	{
		beatsTime.push_back(nearestBeat);
		return;
	}
	// reject beat that already exists
	if (nearestBeat != *temp)
	{
		beatsTime.insert(temp, nearestBeat);
	}
}

void BeatMapEditor::mouseEvent(RenderWindow& window, Event event)
{

	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		cursorSelected = false;
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (mouseInCircle(window, 1024, 576, 250))
		{
			addCursorToBeatList();
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right))
	{
		list<int>::iterator it = beatsTime.begin();
		while (it != beatsTime.end())
		{
			// for the part slider only
			if (cursorRelToMusicMS >= *it - 2500 && cursorRelToMusicMS <= *it + 2500)
			{
				// erase beat that mouse if over when right mouse is pressed	
				if (mouseInBox(window, 24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - *it) / 2500, 50 + sliderHeight / 2, 10, sliderHeight / 2))
				{
					beatsTime.erase(it);
					break;
				}
			}
			it++;
		}
	}
	

	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && mouseInBox(window, 24 - 5 + sliderLength * cursorRelToMusicMS / musicDurationMS, 1000, 10, sliderHeight))
	{
		cursorSelected = true;
		cursorRelToMusicMS = (mouseViewPos.x - 24 + 5) * musicDurationMS / sliderLength;
		cursorRelToMusicMS = clamp(cursorRelToMusicMS, 0, musicDurationMS);
		sound.setPlayingOffset(milliseconds(cursorRelToMusicMS));
	}
	if (Mouse::isButtonPressed(Mouse::Left) && cursorSelected)
	{
		cursorRelToMusicMS = (mouseViewPos.x - 24 + 5) * musicDurationMS / sliderLength;
		cursorRelToMusicMS = clamp(cursorRelToMusicMS, 0, musicDurationMS);
		sound.setPlayingOffset(milliseconds(cursorRelToMusicMS));
	}
}



