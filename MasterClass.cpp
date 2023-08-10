#include "MasterClass.h"
#include "AssetManager.h"
MasterClass::MasterClass(RenderWindow& window)
{
	this->window = &window;
	loadResources();

	text.setFont(AssetManager::getInstance()->getFont("main font"));
	text.setCharacterSize(20);
	text.setFillColor(Color::White);
	backgroundSprite.setTexture(AssetManager::getInstance()->getTexture("background"));
	this->stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
}

MasterClass::~MasterClass()
{
}



void MasterClass::run()
{
	static sf::Shader shader;
	// if (!shader.loadFromFile("BeatShader.frag", sf::Shader::Fragment))
	// {
	//		std::cout << "error reading shader" << std::endl;
	// }

	while (window->isOpen())
	{
		// Calculate FPS
		Time elapsed = clock.restart();
		text.setPosition(0, 0);
		text.setString(to_string(round(1 / elapsed.asSeconds())));


		Event event;
		bool scrollEntered = false;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed || event.type == Event::KeyReleased)
			{
				keyEvent(event);
			}
			else if (event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased)
			{
				mouseEvent(event);
			}

		}
		if (scrollEntered == false) { firstScroll = true; }

		// change event type to anything other then button pressed. This is for hold functionality
		event.type = Event::Closed;
		mouseEvent(event);

		tick();


		// Render and display
		window->clear(Color(14, 60, 109));
		window->draw(backgroundSprite);
		window->draw(text);

		render();
		window->display();

	}

}

void MasterClass::render()
{
	this->stateManager.getCurrentState().get()->render(*this->window);
}


void MasterClass::tick()
{
	this->stateManager.getCurrentState().get()->tick(*this->window);
}

void MasterClass::keyEvent(Event event)
{
	this->stateManager.getCurrentState().get()->keyEvent(event);
}

void MasterClass::mouseEvent(Event event)
{
	this->stateManager.getCurrentState().get()->mouseEvent(*window, event);
}

void MasterClass::loadResources()
{
	AssetManager *assetManager = AssetManager::getInstance();

	// load fonts
	assetManager->loadFont("main font", "arial.ttf");
	assetManager->loadFont("game font", "Dense-Regular.otf");

	// load textures
	assetManager->loadTexture("background", backgroundImagePath);
	assetManager->loadTexture("frame", "Images/frame.png");
	assetManager->loadTexture("tiles", "Images/tiles.png");
	assetManager->loadTexture("button", "Images/button.png");

}
