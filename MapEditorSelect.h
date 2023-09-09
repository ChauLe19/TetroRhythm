#pragma once
#include <memory>
#include "StateScreen.h"
#include "StateManager.h"
#include "BeatMapEditor.h"

class MapEditorSelect : public StateScreen
{
private:
	Text text;
	Button startButton = Button(Color::White, 50, Color::Transparent, "Start", Vector2f(2048 / 2 - 100, 1000), Vector2f(200, 100), Color(0, 186, 211), Keyboard::Enter);
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

