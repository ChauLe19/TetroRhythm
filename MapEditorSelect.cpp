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

void MapEditorSelect::drawOptions(RenderTexture& window, string option, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(window.getSize().x, 150));
		rect.setPosition(x, y - 150/4);
		rect.setFillColor(Color(0, 186, 211));
		window.draw(rect);

		text.setFillColor(Color::Black);

	}
	else
	{
		text.setFillColor(Color::White);
	}
	text.setPosition(x, y);
	text.setCharacterSize(60);
	text.setString(option);
	window.draw(text);
}
void MapEditorSelect::drawOptions(RenderWindow& window, string options, int x, int y, bool isHighlight)
{
	if (isHighlight)
	{
		RectangleShape rect(Vector2f(800, 150));
		rect.setPosition(x, y - 150/4);
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


void MapEditorSelect::tick(const float & dt, RenderWindow& window)
{
}

void MapEditorSelect::render(RenderWindow& window)
{
	RenderTexture mapsTexture;
	mapsTexture.create(1000, 800);

	mapsTexture.clear(Color::Transparent);
	mapsTexture.display();

	startButton.setHighlight(startButton.mouseInButton(window));

	text.setFillColor(Color::White);
	text.setPosition(100, 50);
	text.setCharacterSize(30);
	text.setString("Enter to continue. Esc to exit to menu. Arrow keys to navigate.");
	window.draw(text);


	int size = maps.size();
	for (int i = 0; i < size; ++i)
	{
		drawOptions(mapsTexture, maps[i].filename().string(), 0, mapsTexture.getSize().y/2 - 150/2 + i * 150 + mapRenderOffset, cursor == i);
	}

	Sprite sprite(mapsTexture.getTexture());
	sprite.setPosition(2048/2 - 800/2, 100);
	window.draw(sprite);

	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(assetManager->getDrawable("back button hl"));
	}
	else
	{
		window.draw(assetManager->getDrawable("back button"));
	}
	startButton.render(window, text);
}

void MapEditorSelect::keyEvent(const float & dt, Event event)
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
		mapRenderOffset = -cursor * 150;
		break;
	case Keyboard::Key::Down:
		cursor = clamp(cursor + 1, 0, (int)maps.size() - 1);
		mapRenderOffset = -cursor * 150;
		break;
	}
}

void MapEditorSelect::mouseEvent(const float & dt, RenderWindow& window, Event event)
{
	if (event.type == Event::MouseButtonPressed && mouseInBox(window, 2048/2 - 800/2, 100, 1000, 800))
	{
		isPressed = true;
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
		pressedPosition = Vector2f(mouseViewPos.x, mouseViewPos.y);
		prevMapRenderOffset = mapRenderOffset;
	}
	else if (isPressed && Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mouseViewPos = window.mapPixelToCoords(pixelPos);
		mapRenderOffset = prevMapRenderOffset;
		mapRenderOffset += mouseViewPos.y - pressedPosition.y;
		cursor = clamp( - (mapRenderOffset - 150/2) / 150, 0, (int)maps.size() - 1);
	}
	else if (event.type == Event::MouseButtonReleased)
	{
		isPressed = false;
		mapRenderOffset = -cursor * 150;
		prevMapRenderOffset = mapRenderOffset;
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (startButton.mouseInButton(window))
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new BeatMapEditor(stateManager, fs::absolute(maps[cursor]).string())));
		}
		else if (mouseInBox(window, 20, 20, 40, 40)) // back button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		}
		else if (mouseInBox(window, 20, 20, 40, 40)) // back button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		}
	}
}
