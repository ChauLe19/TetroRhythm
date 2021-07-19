#include "MasterClass.h"

MasterClass::MasterClass(RenderWindow& window)
{
	this->game = new Game();
	this->keyInput = new KeyInput();
	this->window = &window;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::White);
	font.loadFromFile("arial.ttf");
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
				keyInput->updateKeyEvent(event.key.code);
				keyInput->tick(*game);
			}

		}
		tick();

		window->clear(Color::Black);
		window->draw(text);
		text.setString(to_string(game->getScore()));
		text.setPosition(100, 0);
		window->draw(text);
		render();
		window->display();

	}

}


void MasterClass::render()
{
	game->render(*window);
}

void MasterClass::tick()
{
	game->tick(*window, frameCount);
}


