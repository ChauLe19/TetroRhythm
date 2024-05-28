#include "Menu.h"
#include "Tutorial.h"

Menu::Menu(StateManager &stateManager) : StateScreen(stateManager)
{
	text.setFont(getAssetManager()->getFont("game font"));
	text.setFillColor(sf::Color::White);

	sf::Text playText = sf::Text("PLAY", getAssetManager()->getFont("game font"), 50);
	sf::RectangleShape playRect = sf::RectangleShape(sf::Vector2f(500, 100));
	playRect.setPosition(1024 - 250, 450);
	playRect.setFillColor(sf::Color::Transparent);
	beginButton = Button(playRect, playText, sf::Color::White, sf::Color(0, 186, 211));
	beginButton.setCallback([this]() { this->stateManager.addState(std::unique_ptr<StateScreen>(new GameOptions(this->stateManager))); });

	sf::Text beatMapText = sf::Text("EDIT BEAT MAPS", getAssetManager()->getFont("game font"), 50);
	sf::RectangleShape beatMapRect = sf::RectangleShape(sf::Vector2f(500, 100));
	beatMapRect.setPosition(1024 - 250, 570);
	beatMapRect.setFillColor(sf::Color::Transparent);
	beatmapButton = Button(beatMapRect, beatMapText, sf::Color::White, sf::Color(0, 186, 211));
	beatmapButton.setCallback([this]() { this->stateManager.addState(std::unique_ptr<StateScreen>(new MapEditorSelect(this->stateManager))); });

	sf::Text tutorialText = sf::Text("TUTORIAL", getAssetManager()->getFont("game font"), 50);
	sf::RectangleShape tutorialRect = sf::RectangleShape(sf::Vector2f(500, 100));
	tutorialRect.setPosition(1024 - 250, 690);
	tutorialRect.setFillColor(sf::Color::Transparent);
	tutorialButton = Button(tutorialRect, tutorialText, sf::Color::White, sf::Color(0, 186, 211));
	tutorialButton.setCallback([this]() { this->stateManager.addState(std::unique_ptr<StateScreen>(new Tutorial(this->stateManager))); });

	sf::Text settingsText= sf::Text("Settings", getAssetManager()->getFont("game font"), 40);
	sf::RectangleShape settingsRect = sf::RectangleShape(sf::Vector2f(240, 100));
	settingsRect.setPosition(1024 - 250, 810);
	settingsRect.setFillColor(sf::Color::Transparent);
	settingsButton = Button(settingsRect, settingsText, sf::Color::White, sf::Color(0, 186, 211));
	settingsButton.setCallback([this]() { this->stateManager.addState(std::unique_ptr<StateScreen>(new Settings(this->stateManager))); });

	sf::Text exitText = sf::Text("Exit", getAssetManager()->getFont("game font"), 40);
	sf::RectangleShape exitRect = sf::RectangleShape(sf::Vector2f(240, 100));
	exitRect.setPosition(1024 + 10, 810);
	exitRect.setFillColor(sf::Color::Transparent);
	exitButton = Button(exitRect, exitText, sf::Color::White, sf::Color(0, 186, 211));
	exitButton.setCallback([&]() { stateManager.getContext().window->close(); });
}

Menu::~Menu()
{
}

void Menu::tick(const float & dt, sf::RenderWindow& window)
{
}

void Menu::render(sf::RenderWindow& window)
{
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setString("TetroRhythm");
	text.setPosition(1024 - text.getLocalBounds().width / 2, 100);
	window.draw(text);

	window.draw(beginButton);
	window.draw(settingsButton);
	window.draw(beatmapButton);
	window.draw(tutorialButton);
	window.draw(exitButton);
}

void Menu::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
	if (event.type != Event::KeyPressed) return;
	switch (event.key.code)
	{
	case Keyboard::Key::Return:
		stateManager.addState(std::unique_ptr<StateScreen>(new GameOptions(stateManager)));
		break;
	case Keyboard::Key::C:
		stateManager.addState(std::unique_ptr<StateScreen>(new Settings(stateManager)));
		break;
	case Keyboard::Key::E:
		stateManager.addState(std::unique_ptr<StateScreen>(new MapEditorSelect(stateManager)));
		break;
	}
}

void Menu::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	beginButton.mouseEvent(window, event);
	settingsButton.mouseEvent(window, event);
	beatmapButton.mouseEvent(window, event);
	tutorialButton.mouseEvent(window, event);
	exitButton.mouseEvent(window, event);
	exitButton.getPosition();
}

void Menu::b()
{

}
