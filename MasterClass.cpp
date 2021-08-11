#include "MasterClass.h"
MasterClass::MasterClass(RenderWindow& window)
{
	controlsSettings.autoRepeatRate = 0;
	controlsSettings.delayAutoShift = 6;
	initKeys();
	/*controlsSettings.keyMap = { Keyboard::Key::J, Keyboard::Key::L, Keyboard::Key::A, Keyboard::Key::F,
		Keyboard::Key::S, Keyboard::Key::D, Keyboard::Key::I, Keyboard::Key::K };*/
	this->menu = new Menu();
	this->settings = new Settings(controlsSettings);
	this->gameOptions = new GameOptions(game, controlsSettings);
	this->mapEditorSelect = new MapEditorSelect(beatMapEditor);
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
	ifstream keybindsStream("Config/keybinds.txt");

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



void MasterClass::run()
{

	while (window->isOpen())
	{
		// Calculate FPS
		Time elapsed = clock.restart();
		text.setPosition(0, 0);
		text.setString(to_string(round(1 / elapsed.asSeconds())));


		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed)
			{

				keyEvent(event.key.code);
			}
		}
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
	}
}


void MasterClass::tick()
{
	switch (state)
	{
	case State::MENU:
		menu->tick(*window);
		break;
	case State::GAME:
		game->tick(*window);
		break;
	case State::MAP_EDITOR:
		beatMapEditor->tick(*window);
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
	}
}

void MasterClass::mouseEvent()
{
	switch (state)
	{
	case State::MENU:
		menu->mouseEvent(*window);
		break;
	case State::GAME_OPTIONS:
		gameOptions->mouseEvent(*window);
		break;
	case State::SETTINGS:
		break;
	case State::GAME:
		break;
	case State::MAP_EDITOR_SELECT:
		break;
	case State::MAP_EDITOR:
		beatMapEditor->mouseEvent(*window);
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
