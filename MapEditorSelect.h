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
public:
	MapEditorSelect(StateManager &stateManager);
	~MapEditorSelect();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);


	void drawOptions(RenderWindow& window, string options, int x, int y, bool isHighlight);
};

