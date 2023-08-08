#pragma once
#include "StateScreen.h"
#include "Enums.h"
#include "BeatMapEditor.h"
#include "StateManager.h"
class MapEditorSelect : public StateScreen
{
private:
	Text text;
	Font font;
	vector<fs::path> maps;
	int cursor;
public:
	MapEditorSelect(StateManager &stateManager);
	~MapEditorSelect();

	// StateScreen functions
	//****************************************************
	void tick(RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(Event event);
	void mouseEvent(RenderWindow& window, Event event);


	void openBeatMapEditor(string folderPath);
	void drawOptions(RenderWindow& window, string options, int x, int y, bool isHighlight);
};

