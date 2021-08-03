#include "EndlessGame.h"

EndlessGame::EndlessGame(Controls_Settings& settings) : GameBase(settings)
{
}

EndlessGame::~EndlessGame()
{
}

void EndlessGame::tick(RenderWindow& window)
{
	GameBase::tick(window);
}

void EndlessGame::keyEvent(State& state, Keyboard::Key key)
{
	GameBase::keyEvent(state, key);
}

void EndlessGame::render(RenderWindow& window)
{
	GameBase::render(window);
}
