#include "StateScreen.h"

StateScreen::StateScreen(StateManager& stateManager, Context context) :
	stateManager(stateManager),
	m_context(context)
{
}

StateScreen::~StateScreen()
{
}

AssetManager* StateScreen::getAssetManager() const
{
	return m_context.assetManager;
}

StateScreen::Context::Context(sf::RenderWindow* window, AssetManager* assetManager) : window(window), assetManager(assetManager)
{
}
