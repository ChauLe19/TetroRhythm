#include "MasterClass.h"
#include "AssetManager.h"

// source: https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
sf::View getLetterboxView(RenderWindow* window, sf::View view, float windowWidth, float windowHeight)
{
	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to archieve a letterbox effect.
	// A new view (with a new viewport set) is returned.
	float windowRatio = windowWidth / windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;
	View resultView = window->getDefaultView();

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.
	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	resultView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

	return resultView;
}

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
	while (window->isOpen())
	{
		m_view.setSize(resolutionX, resolutionY);
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
				m_view = getLetterboxView(window, m_view, event.size.width, event.size.height);
			}

		}
		if (scrollEntered == false) { firstScroll = true; }

		// change event type to anything other then button pressed. This is for hold functionality
		event.type = Event::Closed;
		mouseEvent(dt, event);

		tick(dt);


		// Render and display
		window->clear(Color::Transparent);
		window->setView(m_view);
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
