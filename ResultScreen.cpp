#include "ResultScreen.h"
#include "GameBase.h"

ResultScreen::ResultScreen(int accuracyBeatCount[3], int rawScore, int combo)
{
	font.loadFromFile("Dense-Regular.otf");
	text.setFont(font);
	text.setFillColor(Color::White);
	if (2 * (accuracyBeatCount[0] + accuracyBeatCount[1] + accuracyBeatCount[2]) != 0) 
		accuracy = ((float)accuracyBeatCount[1] + 2.0 * (float)accuracyBeatCount[2]) * 100.0 / (2.0 * ((float)accuracyBeatCount[0] + (float)accuracyBeatCount[1] + (float)accuracyBeatCount[2])) ;
	if (accuracy == 100.0)
	{
		letterRanked = "SS";
	}
	else if (accuracy >= 95.0)
	{
		letterRanked = "S";
	}
	else if (accuracy >= 90.0)
	{
		letterRanked = "A";
	}
	else if (accuracy >= 80.0)
	{
		letterRanked = "B";
	}
	else if (accuracy >= 70.0)
	{
		letterRanked = "C";
	}
	else
	{
		letterRanked = "D";
	}
	this->accuracyBeatCount[0] = accuracyBeatCount[0];
	this->accuracyBeatCount[1] = accuracyBeatCount[1];
	this->accuracyBeatCount[2] = accuracyBeatCount[2];
	this->combo = combo;
	this->rawScore = rawScore;
	adjustedScore = accuracy * rawScore / 100;
	//this->game = game;
}

ResultScreen::~ResultScreen()
{
}

void ResultScreen::tick(State& state, RenderWindow& window)
{
}

void ResultScreen::render(RenderWindow& window)
{
	text.setFillColor(Color::White);
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

	text.setPosition(200, 700);
	text.setString("Raw Score: " + to_string(rawScore));
	window.draw(text);

	text.setPosition(1200, 400);
	text.setString("Score: " + to_string(adjustedScore));
	window.draw(text);

	text.setCharacterSize(200);
	text.setPosition(1200, 400);
	text.setString(letterRanked);
	window.draw(text);


}

void ResultScreen::keyEvent(State& state, Keyboard::Key key)
{
	switch (key)
	{
	case Keyboard::Key::Escape:
		state = State::MENU;
		break;
	case Keyboard::Key::R:
		state = State::GAME;
		break;
	}
}
void ResultScreen::keyEvent(State& state, Keyboard::Key key, GameBase*& game)
{
	keyEvent(state, key);
	switch (key)
	{
	case Keyboard::Key::R:
		state = State::GAME;
		game->restart();
		break;
	}
}

void ResultScreen::mouseEvent(State& state, RenderWindow& window)
{
}
