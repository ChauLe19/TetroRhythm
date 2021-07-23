#include "GameOptions.h"

GameOptions::GameOptions(GameBase*& gamePtr, Controls_Settings& settings)
	: gamePtr(gamePtr), settings(settings)
{
	cursorX = 0;
	cursorY = 0;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
}

GameOptions::~GameOptions()
{
}

void GameOptions::tick(RenderWindow& window)
{
}

void GameOptions::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setPosition(100, 100);
	text.setCharacterSize(30);
	text.setString("Game Options");
	window.draw(text);

	text.setPosition(50, 200);
	text.setCharacterSize(20);
	text.setString("Auto Drop Beat"); // get as many points as you can but a beat will force a hard drop
	window.draw(text);

	text.setPosition(50, 300);
	text.setCharacterSize(20);
	text.setString("Drop on Beat"); // drop blocks on the beat receives bonus
	window.draw(text);


}

void GameOptions::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Escape:
		state = State::MENU;
		break;
	case Keyboard::Key::Enter:
		state = State::GAME;
		delete gamePtr;
		gamePtr = new AutoDropGame(settings);
		gamePtr->start();
		break;
	}
}
