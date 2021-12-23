#include "MasterClass.h"
MasterClass::MasterClass(RenderWindow& window)
{
	initKeys();
	initConfig();
	/*controlsSettings.keyMap = { Keyboard::Key::J, Keyboard::Key::L, Keyboard::Key::A, Keyboard::Key::F,
		Keyboard::Key::S, Keyboard::Key::D, Keyboard::Key::I, Keyboard::Key::K };*/
	this->menu = new Menu();
	this->settings = new Settings(controlsSettings);
	this->gameOptions = new GameOptions(game, controlsSettings);
	this->mapEditorSelect = new MapEditorSelect(beatMapEditor);
	int a[3] = { 0,0,0 };
	this->resultScreen = new ResultScreen(a, 0, 0);
	this->window = &window;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::White);
}

MasterClass::~MasterClass()
{
	delete game;
}

void MasterClass::initKeys()
{
	ifstream keybindsStream("Config/Keybinds.txt");

	if (keybindsStream.is_open())
	{
		string key = "";
		int keyVal = 0;
		while (keybindsStream >> key >> keyVal)
		{
			controlsSettings.keybinds[key] = Keyboard::Key(keyVal);
		}
	}
}

void MasterClass::initConfig()
{
	ifstream configStream("Config/Config.txt");

	if (configStream.is_open())
	{
		string key = "";
		int keyVal = 0;
		while (configStream >> key >> keyVal)
		{
			if (key == "DAS")
			{
				controlsSettings.delayAutoShift = keyVal;
			}
			else if (key == "ARR")
			{
				controlsSettings.autoRepeatRate = keyVal;
			}
		}
	}
}



void MasterClass::run()
{

	while (window->isOpen())
	{
		// Calculate FPS
		Time elapsed = clock.restart();
		text.setPosition(0, 0);
		text.setString(to_string(round(1 / elapsed.asSeconds())));


		Event event;
		bool scrollEntered = false;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed)
			{
				keyEvent(event.key.code);
			}
			else if (event.type == Event::MouseWheelMoved)
			{
				scrollEntered = true;
				if (state == State::GAME && firstScroll)
				{
					firstScroll = false;
					game->mouseScrollEvent(event);
				}
			}

		}
		if (scrollEntered == false) { firstScroll = true; }
		mouseEvent();
		tick();


		// Render and display
		window->clear(Color::Black);
		window->draw(text);

		render();
		window->display();

	}

}

void MasterClass::render()
{
	switch (state)
	{
	case State::MENU:
		menu->render(*window);
		break;
	case State::GAME:
		game->render(*window);
		break;
	case State::GAME_OPTIONS:
		gameOptions->render(*window);
		break;
	case State::SETTINGS:
		settings->render(*window);
		break;
	case State::MAP_EDITOR_SELECT:
		mapEditorSelect->render(*window);
		break;
	case State::MAP_EDITOR:
		beatMapEditor->render(*window);
		break;
	case State::GAMEOVER:
		resultScreen->render(*window);
		break;
	}
}


void MasterClass::tick()
{
	switch (state)
	{
	case State::MENU:
		menu->tick(state, *window);
		break;
	case State::GAME:
		game->tick(state, *window, resultScreen);
		break;
	case State::MAP_EDITOR:
		beatMapEditor->tick(state, *window);
		break;
	case State::GAMEOVER:
		resultScreen->tick(state, *window);
		break;
	}
}

void MasterClass::keyEvent(Keyboard::Key key)
{
	switch (state)
	{
	case State::MENU:
		menu->keyEvent(state, key);
		break;
	case State::GAME_OPTIONS:
		gameOptions->keyEvent(state, key);
		break;
	case State::SETTINGS:
		settings->keyEvent(state, key);
		break;
	case State::GAME:
		game->keyEvent(state, key);
		break;
	case State::MAP_EDITOR_SELECT:
		mapEditorSelect->keyEvent(state, key);
		break;
	case State::MAP_EDITOR:
		beatMapEditor->keyEvent(state, key);
		break;
	case State::GAMEOVER:
		resultScreen->keyEvent(state, key, game);
		break;
	}
}

void MasterClass::mouseEvent()
{
	switch (state)
	{
	case State::MENU:
		menu->mouseEvent(state, *window);
		break;
	case State::GAME_OPTIONS:
		gameOptions->mouseEvent(state, *window);
		break;
	case State::SETTINGS:
		break;
	case State::GAME:
		game->mouseEvent(state, *window);
		break;
	case State::MAP_EDITOR_SELECT:
		break;
	case State::MAP_EDITOR:
		beatMapEditor->mouseEvent(state, *window);
		break;
	case State::GAMEOVER:
		resultScreen->mouseEvent(state, *window);
		break;
	}
}

void MasterClass::openBeatMapEditor(string folderPath)
{
	if (state == State::MAP_EDITOR_SELECT)
	{
		mapEditorSelect->openBeatMapEditor(state, folderPath);
	}
}
