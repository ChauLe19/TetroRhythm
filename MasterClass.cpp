#include "MasterClass.h"

MasterClass::MasterClass(RenderWindow& window)
{
	this->game = new Game();
	this->keyInput = new KeyInput();
	this->menu = new Menu();
	this->config = new Config();
	this->window = &window;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::White);
}

MasterClass::~MasterClass()
{
	delete game;
	delete keyInput;
}

void MasterClass::run()
{

	while (window->isOpen())
	{
		// FPS
		Time elapsed = clock.restart();
		text.setPosition(0, 0);
		text.setString(to_string(round(1 / elapsed.asSeconds())));

		frameCount++;

		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed)
			{
				cout << "press" << endl;
				keyInput->updateKeyEvent(state, event.key.code);
				keyInput->noHoldKeyEvent(state, event.key.code, *game, *config);
			}
		}
		keyInput->tick(state, *game);
		tick();

		window->clear(Color::Black);
		window->draw(text);
		text.setString(to_string(game->getScore()));
		text.setPosition(100, 0);
		window->draw(text);
		if (game->getIsGameOver())
		{
			text.setString("GAME OVER");
			text.setPosition(300, 0);
			window->draw(text);
			text.setString("Press R to restart");
			text.setPosition(270, 20);
			window->draw(text);
		}
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
	case State::SETTINGS:
		config->render(*window, keyInput->getKeyMap());
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
		game->tick(*window, frameCount);
		break;
	}
}


