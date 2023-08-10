#include "MapEditorSelect.h"
#include "Menu.h"


MapEditorSelect::MapEditorSelect(StateManager &stateManager) : StateScreen(stateManager)
{
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);


	cursor = 0;
	std::string path = "BeatMaps";
	for (const auto& entry : fs::directory_iterator(path))
	{
		maps.push_back(entry.path());
	}
}

MapEditorSelect::~MapEditorSelect()
{
}

void MapEditorSelect::drawOptions(RenderWindow& window, string options, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(800, 100));
		rect.setPosition(x, y - 25);
		rect.setFillColor(Color::White);
		window.draw(rect);

		text.setFillColor(Color::Black);

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y);
	text.setCharacterSize(60);
	text.setString(options);
	window.draw(text);

}


void MapEditorSelect::tick(RenderWindow& window)
{
}

void MapEditorSelect::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
	text.setPosition(100, 50);
	text.setCharacterSize(30);
	text.setString("Enter to continue. Esc to exit to menu. Arrow keys to navigate.");
	window.draw(text);


	int tempCursor = cursor - 2;
	int size = maps.size();
	for (int i = 0; i < 5 && tempCursor < size; ++tempCursor, ++i)
	{
		if (tempCursor >= 0)
		{
			drawOptions(window, maps[tempCursor].filename().string(), 600, 100 + i * 200, cursor == tempCursor);
		}
	}
}

void MapEditorSelect::keyEvent(Event event)
{
	if (event.type != Event::KeyPressed) return;
	Keyboard::Key key = event.key.code;
	switch (key)
	{
	case Keyboard::Key::Return:
		stateManager.addState(std::unique_ptr<StateScreen>(new BeatMapEditor(stateManager, fs::absolute(maps[cursor]).string())));
		break;
	case Keyboard::Key::Escape:
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		break;
	case Keyboard::Key::Up:
		cursor = clamp(cursor - 1, 0, (int)maps.size() - 1);
		break;
	case Keyboard::Key::Down:
		cursor = clamp(cursor + 1, 0, (int)maps.size() - 1);
		break;
	}
}

void MapEditorSelect::mouseEvent(RenderWindow& window, Event event)
{
}
