#include "ResultScreen.h"
#include "Menu.h"
#include "GameBase.h"

ResultScreen::ResultScreen(StateManager& stateManager, Context context, std::string songName, int accuracyBeatCount[3], int rawScore, int combo) : StateScreen(stateManager, context), songName(songName)
{
	text.setFont(getAssetManager()->getFont("game font"));
	text.setFillColor(sf::Color::White);
	if (2 * (accuracyBeatCount[0] + accuracyBeatCount[1] + accuracyBeatCount[2]) != 0) 
		accuracy = ((float)accuracyBeatCount[1] + 2.0 * (float)accuracyBeatCount[2]) * 100.0 / (2.0 * ((float)accuracyBeatCount[0] + (float)accuracyBeatCount[1] + (float)accuracyBeatCount[2])) ;
	this->accuracyBeatCount[0] = accuracyBeatCount[0];
	this->accuracyBeatCount[1] = accuracyBeatCount[1];
	this->accuracyBeatCount[2] = accuracyBeatCount[2];
	this->combo = combo;
	this->rawScore = rawScore;
	this->rawScore = rawScore;
	this->adjustedScore = rawScore;
	std::map<std::string, int> thresholds = GameSettings::getInstance()->getHighscores()->dropToBeatThreshold;
	int threshold = thresholds.find(songName) != thresholds.end() ? thresholds.at(songName) : 1;
	this->letterRanked = getRank(rawScore, threshold);
}

ResultScreen::~ResultScreen()
{
}

void ResultScreen::tick(const float & dt, sf::RenderWindow& window)
{
}

void ResultScreen::render(sf::RenderWindow& window)
{
	using namespace std;
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(60);

	text.setPosition(200, 200);
	text.setString("Accuracy: " + to_string(accuracy) + "%");
	window.draw(text);

	text.setPosition(200, 300);
	text.setString("Miss/Too late: " + to_string(accuracyBeatCount[0]));
	window.draw(text);
	text.setPosition(200, 400);
	text.setString("Almost: " + to_string(accuracyBeatCount[1]));
	window.draw(text);
	text.setPosition(200, 500);
	text.setString("Hit: " + to_string(accuracyBeatCount[2]));
	window.draw(text);
	text.setPosition(200, 600);
	text.setString("Combo: " + to_string(combo));
	window.draw(text);


	text.setCharacterSize(500);
	text.setPosition(1200, 200);
	text.setString(letterRanked);
	window.draw(text);
	text.setPosition(1000, 700);
	text.setString("Score: " + to_string(adjustedScore));
	text.setCharacterSize(150);
	window.draw(text);

	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(getAssetManager()->getDrawable("back button hl"));
	}
	else
	{
		window.draw(getAssetManager()->getDrawable("back button"));
	}

}

void ResultScreen::keyEvent(const float & dt, sf::Event event)
{
	using namespace sf;
	if (event.type != Event::KeyPressed) return;
	switch (event.key.code)
	{
	case Keyboard::Key::Escape:
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager, m_context)));
		break;
	case Keyboard::Key::R:
		stateManager.addState(std::unique_ptr<StateScreen>(new DropToTheBeatGame(stateManager, m_context, fs::current_path().append("BeatMaps").append(songName).string())));
		break;
	}
}

void ResultScreen::mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager, m_context)));
	}
}
