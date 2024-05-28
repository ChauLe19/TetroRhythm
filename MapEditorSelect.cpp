#include "MapEditorSelect.h"
#include "Menu.h"
#include "Styles.h"


MapEditorSelect::MapEditorSelect(StateManager &stateManager, Context context) : StateScreen(stateManager, context)
{
	using namespace sf;
	text.setFont(getAssetManager()->getFont("game font"));
	text.setFillColor(Color::White);

	startButton.setShortcut(sf::Keyboard::Enter);
	startButton.setBaseColor(TRStyles::btnBaseColor);
	startButton.setHighlightColor(TRStyles::btnHLColor);
	startButton.setSize(Vector2f(200, 100));
	startButton.setPosition(Vector2f(2048 / 2 - 100, 1000));

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

void MapEditorSelect::drawOptions(sf::RenderTexture& window, std::string option, int x, int y, bool isHighlight)
{
	using namespace sf;
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
void MapEditorSelect::drawOptions(sf::RenderWindow& window, std::string options, int x, int y, bool isHighlight)
{
	using namespace sf;
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


void MapEditorSelect::tick(const float & dt, sf::RenderWindow& window)
{
}

void MapEditorSelect::render(sf::RenderWindow& window)
{
	using namespace sf;
	RenderTexture mapsTexture;
	mapsTexture.create(1000, 800);

	mapsTexture.clear(Color::Transparent);
	mapsTexture.display();

	text.setFillColor(Color::White);
	text.setCharacterSize(80);
	text.setString("Select map to edit");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 50);
	window.draw(text);

	int size = maps.size();
	for (int i = 0; i < size; ++i)
	{
		drawOptions(mapsTexture, maps[i].filename().string(), 0, mapsTexture.getSize().y/2 - 150/2 + i * 150 + mapRenderOffset, cursor == i);
	}

	Sprite sprite(mapsTexture.getTexture());
	sprite.setPosition(2048/2 - 800/2, 150);
	window.draw(sprite);

	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(getAssetManager()->getDrawable("back button hl"));
	}
	else
	{
		window.draw(getAssetManager()->getDrawable("back button"));
	}
	window.draw(startButton);
}

void MapEditorSelect::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
	using namespace std;
	if (event.type != Event::KeyPressed) return;
	Keyboard::Key key = event.key.code;
	switch (key)
	{
	case Keyboard::Key::Return:
		stateManager.addState(std::unique_ptr<StateScreen>(new BeatMapEditor(stateManager, m_context, fs::absolute(maps[cursor]).string())));
		break;
	case Keyboard::Key::Escape:
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager, m_context)));
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

void MapEditorSelect::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
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
		cursor = std::clamp( - (mapRenderOffset - 150/2) / 150, 0, (int)maps.size() - 1);
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
			stateManager.addState(std::unique_ptr<StateScreen>(new BeatMapEditor(stateManager, m_context, fs::absolute(maps[cursor]).string())));
		}
		else if (mouseInBox(window, 20, 20, 40, 40)) // back button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager, m_context)));
		}
		else if (mouseInBox(window, 20, 20, 40, 40)) // back button
		{
			stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager, m_context)));
		}
	}
}

void MapEditorSelect::mouseScrollEvent(const float& dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace std;
	if (event.type == sf::Event::MouseWheelScrolled && mouseInBox(window, 2048/2 - 800/2, 150, 1000, 800))
	{
		cursor = clamp(cursor - (int) event.mouseWheelScroll.delta, 0, (int)maps.size() - 1);
		mapRenderOffset = -cursor * 150;
		prevMapRenderOffset = mapRenderOffset;
	}
}
