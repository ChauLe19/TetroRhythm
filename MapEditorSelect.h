#pragma once
#include <memory>
#include "StateScreen.h"
#include "StateManager.h"
#include "BeatMapEditor.h"

class MapEditorSelect : public StateScreen
{
private:
	Text text;
	vector<fs::path> maps;
	int cursor;
	int mapRenderOffset = 0;
	bool isPressed = false;
	Vector2f pressedPosition;
	int prevMapRenderOffset = mapRenderOffset;
	int cursorMap = 0; // current index of map
public:
	MapEditorSelect(StateManager &stateManager);
	~MapEditorSelect();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);


private:
	void drawOptions(RenderTexture& window, string option, int x, int y, bool isHighlight);
	void drawOptions(RenderWindow& window, string options, int x, int y, bool isHighlight);
};

