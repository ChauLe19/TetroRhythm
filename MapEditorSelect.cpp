#include "MapEditorSelect.h"

MapEditorSelect::MapEditorSelect(BeatMapEditor*& mapEditor) : mapEditor(mapEditor)
{
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
}

MapEditorSelect::~MapEditorSelect()
{
}

void MapEditorSelect::tick(RenderWindow& window)
{
}

void MapEditorSelect::render(RenderWindow& window)
{
	text.setPosition(200, 100);
	text.setCharacterSize(20);
	text.setString("Chose Tetris_theme.wav. Press Enter to continue.");
	window.draw(text);
}

void MapEditorSelect::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Enter:
		mapEditor = new BeatMapEditor(importedPath);
		state = State::MAP_EDITOR;
		break;
	case Keyboard::Key::C:
		state = State::SETTINGS;
		break;
	case Keyboard::Key::E:
		state = State::MAP_EDITOR_SELECT;
		break;
	case Keyboard::Key::Escape:
		state = State::MENU;
		break;
	}
}

void MapEditorSelect::mouseEvent(RenderWindow& window)
{
}

void MapEditorSelect::openBeatMapEditor(State& state, string folderPath)
{
	mapEditor = new BeatMapEditor(folderPath);
	state = State::MAP_EDITOR;
}
