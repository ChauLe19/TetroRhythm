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
	backgroundSprite.setColor(Color(255, 255, 255, 100));
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


		updateDt();
		Event event;
		bool scrollEntered = false;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed || event.type == Event::KeyReleased)
			{
				keyEvent(dt, event);
			}
			else if (event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased || event.type == Event::MouseMoved)
			{
				mouseEvent(dt, event);
			}
			else if (event.type == Event::MouseWheelScrolled)
			{
				mouseScrolledEvent(dt, event);
			}
			else if (event.type == Event::Resized)
			{
				float m_window_width = event.size.width;
				float m_window_height = event.size.height;
				float m_initial_aspect_ratio = resolutionX / float(resolutionY);
				float new_width = m_initial_aspect_ratio * m_window_height;
				float new_height = m_window_width / m_initial_aspect_ratio;
				float offset_width = (m_window_width - new_width) / 2.0;
				float offset_height = (m_window_height - new_height) / 2.0;
				sf::View view = window->getDefaultView();
				if (m_window_width >= m_initial_aspect_ratio * m_window_height) {
					view.setViewport(sf::FloatRect(offset_width / m_window_width, 0.0, new_width / m_window_width, 1.0));
				}
				else {
					view.setViewport(sf::FloatRect(0.0, offset_height / m_window_height, 1.0, new_height / m_window_height));
				}

				window->setView(view);
			}

		}
		if (scrollEntered == false) { firstScroll = true; }

		// change event type to anything other then button pressed. This is for hold functionality
		event.type = Event::Closed;
		mouseEvent(dt, event);

		tick(dt);


		// Render and display
		window->clear(Color::Transparent);
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


void MasterClass::tick(const float & dt)
{
	this->stateManager.getCurrentState().get()->tick(dt, *this->window);
}

void MasterClass::keyEvent(const float & dt, Event event)
{
	this->stateManager.getCurrentState().get()->keyEvent(dt, event);
}

void MasterClass::mouseEvent(const float & dt, Event event)
{
	this->stateManager.getCurrentState().get()->mouseEvent(dt, *window, event);
}

void MasterClass::mouseScrolledEvent(const float& dt, Event event)
{
	this->stateManager.getCurrentState().get()->mouseScrollEvent(dt, *window, event);
}

void MasterClass::updateDt()
{
	this->dt = this->clock.restart().asSeconds();
}

void MasterClass::loadResources()
{
	AssetManager *assetManager = AssetManager::getInstance();

	// load fonts
	assetManager->loadFont("main font", "ChakraPetch-Regular.ttf");
	assetManager->loadFont("game font", "ChakraPetch-Bold.ttf");

	// load textures
	assetManager->loadTexture("background", backgroundImagePath);
	assetManager->loadTexture("tiles", "Images/tiles.png");
	assetManager->loadTexture("instruction", "Images/instruction.png");

	sf::ConvexShape *backButton = new ConvexShape();
	backButton->setPointCount(8);
	backButton->setPoint(0, sf::Vector2f(20, 0));
	backButton->setPoint(1, sf::Vector2f(0, 20));
	backButton->setPoint(2, sf::Vector2f(20, 40));
	backButton->setPoint(3, sf::Vector2f(20, 30));
	backButton->setPoint(4, sf::Vector2f(40, 30));
	backButton->setPoint(5, sf::Vector2f(40, 10));
	backButton->setPoint(6, sf::Vector2f(20, 10));
	backButton->setPoint(7, sf::Vector2f(20, 0));
	backButton->setPosition(20, 20);
	backButton->setFillColor(Color::White);
	assetManager->loadDrawable("back button", std::unique_ptr<Drawable>(backButton));

	sf::ConvexShape *backButtonHL = new ConvexShape();
	backButtonHL->setPointCount(8);
	backButtonHL->setPoint(0, sf::Vector2f(20, 0));
	backButtonHL->setPoint(1, sf::Vector2f(0, 20));
	backButtonHL->setPoint(2, sf::Vector2f(20, 40));
	backButtonHL->setPoint(3, sf::Vector2f(20, 30));
	backButtonHL->setPoint(4, sf::Vector2f(40, 30));
	backButtonHL->setPoint(5, sf::Vector2f(40, 10));
	backButtonHL->setPoint(6, sf::Vector2f(20, 10));
	backButtonHL->setPoint(7, sf::Vector2f(20, 0));
	backButtonHL->setPosition(20, 20);
	backButtonHL->setFillColor(Color(0, 186, 211));
	assetManager->loadDrawable("back button hl", std::unique_ptr<Drawable>(backButtonHL));
}
