#include "BeatMapEditor.h"
#include "Menu.h"
#include "Styles.h"
#include <memory>

BeatMapEditor::BeatMapEditor(StateManager &stateManager, std::string folderPath) : StateScreen(stateManager)
{
	using namespace sf;
	using namespace std;
	loadStaticAssets();
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);

	beatButton.setBaseColor(sf::Color::Black);
	beatButton.setFillColor(sf::Color(255, 255, 255, 200));
	beatButton.setHighlightColor(TRStyles::btnHLColor);
	beatButton.setSize(sf::Vector2f(400, 400));
	beatButton.setPosition(sf::Vector2f(1024 + 1024 / 2 - 200, 1152 / 2 - 200));
	beatButton.setCallback(std::bind(&BeatMapEditor::addCursorToBeatList, this));
	
	speedButton025 = new Button(sf::Text("x0.25", assetManager->getFont("game font"), 35));
	speedButton025->setHighlightColor(TRStyles::btnHLColor);
	speedButton025->setFillColor(TRStyles::btnFillColor);
	speedButton025->setSize(sf::Vector2f(120, 60));
	speedButton025->setPosition(sf::Vector2f(2048 - 3 * 170, 1152 - sliderHeight - 70));
	speedButton025->setShortcut(Keyboard::Key::Num2);
	speedButton025->setSelectable(true);
	speedButton025->setCallback([this]() { sound.setPitch(0.25); });

	speedButton050 = new Button(sf::Text("x0.50", assetManager->getFont("game font"), 35));
	speedButton050->setHighlightColor(TRStyles::btnHLColor);
	speedButton050->setFillColor(TRStyles::btnFillColor);
	speedButton050->setSize(sf::Vector2f(120, 60));
	speedButton050->setPosition(sf::Vector2f(2048 - 2 * 170, 1152 - sliderHeight - 70));
	speedButton050->setShortcut(Keyboard::Key::Num5);
	speedButton050->setSelectable(true);
	speedButton050->setCallback([this]() { sound.setPitch(0.5); });

	speedButton100 = new Button(sf::Text("x1", assetManager->getFont("game font"), 35));
	speedButton100->setHighlightColor(TRStyles::btnHLColor);
	speedButton100->setFillColor(TRStyles::btnFillColor);
	speedButton100->setSize(sf::Vector2f(120, 60));
	speedButton100->setPosition(sf::Vector2f(2048 - 170, 1152 - sliderHeight - 70));
	speedButton100->setShortcut(Keyboard::Key::Num1);
	speedButton100->setSelectable(true);
	speedButton100->setCallback([this]() { sound.setPitch(1); });

	speedButtonGroup.addButton(speedButton025);
	speedButtonGroup.addButton(speedButton050);
	speedButtonGroup.addButton(speedButton100);
	speedButton100->setSelected(true);

	dividerButton1 = new Button(sf::Text("1", assetManager->getFont("game font"), 35));
	dividerButton1->setHighlightColor(TRStyles::btnHLColor);
	dividerButton1->setFillColor(TRStyles::btnFillColor);
	dividerButton1->setSize(sf::Vector2f(120, 60));
	dividerButton1->setPosition(sf::Vector2f(2048 - 170, sliderHeight + 10));
	dividerButton1->setSelectable(true);
	dividerButton1->setCallback([this]() { setDivider(1); });

	dividerButton12 = new Button(sf::Text("1/2", assetManager->getFont("game font"), 35));
	dividerButton12->setHighlightColor(TRStyles::btnHLColor);
	dividerButton12->setFillColor(TRStyles::btnFillColor);
	dividerButton12->setSize(sf::Vector2f(120, 60));
	dividerButton12->setPosition(sf::Vector2f(2048 - 2 * 170, sliderHeight + 10));
	dividerButton12->setSelectable(true);
	dividerButton12->setCallback([this]() { setDivider(2); });

	dividerButton13 = new Button(sf::Text("1/3", assetManager->getFont("game font"), 35));
	dividerButton13->setHighlightColor(TRStyles::btnHLColor);
	dividerButton13->setFillColor(TRStyles::btnFillColor);
	dividerButton13->setSize(sf::Vector2f(120, 60));
	dividerButton13->setPosition(sf::Vector2f(2048 - 3 * 170, sliderHeight + 10));
	dividerButton13->setSelectable(true);
	dividerButton13->setCallback([this]() { setDivider(3); });

	dividerButton14 = new Button(sf::Text("1/4", assetManager->getFont("game font"), 35));
	dividerButton14->setHighlightColor(TRStyles::btnHLColor);
	dividerButton14->setFillColor(TRStyles::btnFillColor);
	dividerButton14->setSize(sf::Vector2f(120, 60));
	dividerButton14->setPosition(sf::Vector2f(2048 - 4 * 170, sliderHeight + 10));
	dividerButton14->setSelectable(true);
	dividerButton14->setCallback([this]() { setDivider(4); });

	dividerButtonGroup.addButton(dividerButton1);
	dividerButtonGroup.addButton(dividerButton12);
	dividerButtonGroup.addButton(dividerButton13);
	dividerButtonGroup.addButton(dividerButton14);
	dividerButton1->setSelected(true);

	fs::path audioPath = folderPath;
	audioPath.append(audioPath.filename().string());
	audioPath = AssetManager::getAudioFilePathExtension(audioPath);
	std::cout << audioPath.string() << std::endl;
	buffer.loadFromFile(audioPath.string()); // TODO: add error catching
	sound.setBuffer(buffer);

	fs::path txtPath = folderPath;
	txtPath.append(txtPath.filename().string() + ".txt");

	if (!fs::exists(txtPath))
	{
		cerr << "Text file doesn't exist." << endl;
		ofstream newBeatMapTextFile(txtPath);
		newBeatMapTextFile.close();
	}


	this->textFilePath = fs::absolute(txtPath).string(); // change to text file file with audio file path



	musicDurationMS = buffer.getDuration().asMilliseconds();

	std::ifstream inFile;
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


void BeatMapEditor::loadStaticAssets()
{
	using namespace sf;
	CircleShape *playButton = new CircleShape(20, 3);
	playButton->setFillColor(Color::White);
	playButton->setPosition(80, 1152 - sliderHeight - 40);
	playButton->rotate(90);

	RectangleShape *leftPause = new RectangleShape();
	leftPause->setSize(Vector2f(10, 40));
	leftPause->setFillColor(Color::White);
	leftPause->setPosition(50, 1152 - sliderHeight - 40);

	RectangleShape *rightPause = new RectangleShape();
	rightPause->setSize(Vector2f(10, 40));
	rightPause->setFillColor(Color::White);
	rightPause->setPosition(70, 1152 - sliderHeight - 40);

	RectangleShape *wholeAudioSlider = new RectangleShape(); // a slider of the whole audio file
	wholeAudioSlider->setSize(Vector2f(2048, sliderHeight * 2/3));
	wholeAudioSlider->setFillColor(Color(0, 0, 0, 150));
	wholeAudioSlider->setOutlineColor(Color::Transparent);
	wholeAudioSlider->setOutlineThickness(5);
	wholeAudioSlider->setPosition(0, 1152 - sliderHeight);

	RectangleShape *partAudioSlider = new RectangleShape(); // a slider show only 5 sec part of the audio at the cursor
	partAudioSlider->setSize(Vector2f(2048, sliderHeight));
	partAudioSlider->setOutlineColor(Color::Transparent);
	partAudioSlider->setOutlineThickness(5);
	partAudioSlider->setFillColor(Color(0, 0, 0, 150));
	partAudioSlider->setPosition(0, 0);


	RectangleShape *partAudioCursor = new RectangleShape(); // cursor for part audio slider
	partAudioCursor->setSize(Vector2f(10, sliderHeight));
	partAudioCursor->setFillColor(Color(245, 222, 72));
	partAudioCursor->setPosition(24 - 5 + sliderLength / 2, 0); // middle of slider

	CircleShape *beatButton = new CircleShape();
	beatButton->setRadius(250);
	beatButton->setPosition(1024 - 250, 576 - 250);
	beatButton->setFillColor(Color::White);

	CircleShape *beatHLButton = new CircleShape();
	beatHLButton->setRadius(250);
	beatHLButton->setPosition(1024 - 250, 576 - 250);
	beatHLButton->setFillColor(Color(0, 186, 211));

	assetManager->loadDrawable("play button", std::unique_ptr<sf::Drawable>(playButton));
	assetManager->loadDrawable("left pause", std::unique_ptr<sf::Drawable>(leftPause));
	assetManager->loadDrawable("right pause", std::unique_ptr<sf::Drawable>(rightPause));
	assetManager->loadDrawable("whole audio slider", std::unique_ptr<sf::Drawable>(wholeAudioSlider));
	assetManager->loadDrawable("part audio slider", std::unique_ptr<sf::Drawable>(partAudioSlider));
	assetManager->loadDrawable("part audio cursor", std::unique_ptr<sf::Drawable>(partAudioCursor));
	assetManager->loadDrawable("beat button", std::unique_ptr<sf::Drawable>(beatButton));
	assetManager->loadDrawable("beat highlight button", std::unique_ptr<sf::Drawable>(beatHLButton));
}

void BeatMapEditor::setDivider(int divider)
{
	this->divider = divider;
}

BeatMapEditor::~BeatMapEditor()
{
	delete speedButton025;
	delete speedButton050;
	delete speedButton100;
}

void BeatMapEditor::save()
{
	using namespace std;
	std::ofstream outFile;
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

void BeatMapEditor::tick(const float & dt, sf::RenderWindow& window)
{
	using namespace sf;
	if (sound.getStatus() == Music::Status::Stopped)
	{
		sound.play();
		sound.pause();
		sound.setPlayingOffset(milliseconds(musicDurationMS));
	}
	cursorRelToMusicMS = sound.getPlayingOffset().asMilliseconds();
}

void BeatMapEditor::render(sf::RenderWindow& window)
{
	using namespace sf;
	using namespace std;
	simulatorBoard.render(window);
	window.draw(beatButton);
	window.draw(*speedButton025);
	window.draw(*speedButton050);
	window.draw(*speedButton100);
	window.draw(*dividerButton1);
	window.draw(*dividerButton12);
	window.draw(*dividerButton13);
	window.draw(*dividerButton14);

	text.setFillColor(Color(255, 255, 255, 100));
	text.setCharacterSize(30);
	text.setString("Right click over the beat to delete it");
	text.setPosition(100, sliderHeight);
	window.draw(text);



	if (sound.getStatus() != Music::Status::Playing) // draw playing status
	{
		window.draw(assetManager->getDrawable("play button"));
	}
	else
	{
		window.draw(assetManager->getDrawable("left pause"));
		window.draw(assetManager->getDrawable("right pause"));
	}

	window.draw(assetManager->getDrawable("whole audio slider"));
	window.draw(assetManager->getDrawable("part audio slider"));
	window.draw(assetManager->getDrawable("part audio cursor"));

	RectangleShape wholeAudioCursor; // cursor for whole audio slider
	wholeAudioCursor.setSize(Vector2f(10, sliderHeight * 2 / 3));
	wholeAudioCursor.setFillColor(Color::Yellow);
	wholeAudioCursor.setOutlineColor(Color::Yellow);
	wholeAudioCursor.setPosition(24 - 5 + sliderLength * cursorRelToMusicMS / musicDurationMS, 1152 - sliderHeight * 2 /3);
	window.draw(wholeAudioCursor);

	std::list<int>::iterator it = beatsTime.begin(); // draw beats
	int count = 0;
	int currentBeatIndex = 0;
	while (it != beatsTime.end())
	{
		count++;

		// draw the bottom beats (the entire audio)
		RectangleShape beat;
		beat.setSize(Vector2f(4, sliderHeight / 2));
		beat.setFillColor(Color::Red);
		beat.setPosition(24 - 2 + sliderLength * (*it) / musicDurationMS, 1152 - sliderHeight / 2);
		window.draw(beat);

		// draw the top beats (the closeup audio)
		if (cursorRelToMusicMS >= *it - 2500 && cursorRelToMusicMS <= *it + 2500)
		{
			RectangleShape beatInPartSlider;
			beatInPartSlider.setSize(Vector2f(10, sliderHeight * 2 / 3));
			beatInPartSlider.setFillColor(Color::Red);
			beatInPartSlider.setPosition(24 - 10 / 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - *it) / 2500, sliderHeight / 3);
			window.draw(beatInPartSlider);
		}

		if (cursorRelToMusicMS >= *it)
		{
			currentBeatIndex = count;
		}

		it++;

	}

	text.setFillColor(Color(255, 255, 255, 50));
	text.setCharacterSize(100);
	text.setString("Preview");
	text.setPosition(100 + (boardSquareSize*boardWidth)/2 - text.getLocalBounds().width/2, 1152 / 2 - (boardSquareSize * boardHeight) / 2 + 2* boardSquareSize);
	window.draw(text);
	simulatorBoard.setBoard(infBoardSimulation.at(currentBeatIndex % infBoardSimulation.size()));
	Board simulatorBoard = Board(100, 1152 / 2 - (boardSquareSize * boardHeight)/2);


	// render major/minor notes
	// major notes occur every 4 minor notes
	for (int i = std::ceil((float)(cursorRelToMusicMS - 2500) / ((float)mspb / divider)); i <= std::floor((float)(cursorRelToMusicMS + 2500) / ((float)mspb / divider)); i++)
	{
		RectangleShape beatInPartSlider;
		beatInPartSlider.setSize(Vector2f(4, sliderHeight / 4));
		beatInPartSlider.setFillColor(i % divider == 0 ? Color::White : Color(0, 159, 180));
		int t = i * (float)mspb / divider;
		beatInPartSlider.setPosition(24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - t) / 2500, sliderHeight * 3 / 8);
		window.draw(beatInPartSlider);
	}

	//window.draw(assetManager->getDrawable("beat button"));

	// draw audio timestamp
	text.setFillColor(Color::White);
	Int32 tleft = sound.getPlayingOffset().asMilliseconds();
	Int32 tTotal = sound.getBuffer()->getDuration().asMilliseconds();
	String tLeftString = getPaddingString(std::to_string(tleft / 1000 / 60), 2, '0', false) + ":"
		+ getPaddingString(to_string(tleft / 1000 % 60), 2, ' 0', false) + ":" 
		+ getPaddingString(to_string(tleft % 1000), 3, '0', false);
	String tTotalString = getPaddingString(to_string(tTotal / 1000 / 60), 2, '0', false) + ":"
		+ getPaddingString(to_string(tTotal / 1000 % 60), 2, ' 0', false) + ":" 
		+ getPaddingString(to_string(tTotal % 1000), 3, '0', false);
	text.setCharacterSize(35);
	text.setString(tLeftString);
	text.setPosition(100, 1152 - sliderHeight - 40);
	window.draw(text);
	text.setString("/");
	text.setPosition(290, 1152 - sliderHeight - 40);
	window.draw(text);
	text.setPosition(330, 1152 - sliderHeight - 40);
	text.setString(tTotalString);
	window.draw(text);

	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(assetManager->getDrawable("back button hl"));
	}
	else
	{
		window.draw(assetManager->getDrawable("back button"));
	}
}

void BeatMapEditor::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
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
	int nearestBeat = std::round((float)(cursorRelToMusicMS) / ((float)mspb / divider));
	nearestBeat = nearestBeat * ((float)mspb / divider);
	std::list<int>::iterator temp = beatsTime.begin();
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

void BeatMapEditor::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	using namespace std;

	beatButton.mouseEvent(window, event);
	speedButton025->mouseEvent(window, event);
	speedButton050->mouseEvent(window, event);
	speedButton100->mouseEvent(window, event);
	dividerButton1->mouseEvent(window, event);
	dividerButton12->mouseEvent(window, event);
	dividerButton13->mouseEvent(window, event);
	dividerButton14->mouseEvent(window, event);

	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		cursorSelected = false;
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{

		if (mouseInBox(window, 50, 1152 - sliderHeight - 40, 30, 40))
		{
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
		else if (mouseInBox(window, 20, 20, 40, 40)) // back button
		{
			save();
			sound.stop();
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
			return;
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
				if (mouseInBox(window, 24 - 2 + sliderLength / 2 - sliderLength / 2 * (cursorRelToMusicMS - *it) / 2500, sliderHeight / 2, 10, sliderHeight / 2))
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
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && mouseInBox(window, 0, 1152 - sliderHeight, sliderLength, sliderHeight))
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



