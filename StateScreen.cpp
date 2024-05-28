#include "StateScreen.h"
#include "StateManager.h"

StateScreen::StateScreen(StateManager& stateManager) :
	stateManager(stateManager)
{
}

StateScreen::~StateScreen()
{
}

AssetManager* StateScreen::getAssetManager() const
{
	return stateManager.getContext().assetManager;
}
