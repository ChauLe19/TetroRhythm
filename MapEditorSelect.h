#pragma once
#include <memory>
#include "StateScreen.h"
#include "StateManager.h"
#include "BeatMapEditor.h"

class MapEditorSelect : public StateScreen
{
private:
	sf::Text text;
	Button startButton = Button(sf::Text("Start", getAssetManager()->getFont("game font"), 50U));
	std::vector<fs::path> maps;
	int cursor = 0;
	int mapRenderOffset = 0;
	bool isPressed = false;
	sf::Vector2f pressedPosition;
	int prevMapRenderOffset = mapRenderOffset;
public:
	MapEditorSelect(StateManager &stateManager);
	~MapEditorSelect();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);
	void mouseScrollEvent(const float & dt, sf::RenderWindow& window, sf::Event event);


private:
	void drawOptions(sf::RenderTexture& window, std::string option, int x, int y, bool isHighlight);
	void drawOptions(sf::RenderWindow& window, std::string options, int x, int y, bool isHighlight);
};

