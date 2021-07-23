// TetroRythm.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Initilize Masterclass and window. Start game

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameBase.h"
#include "MasterClass.h"

using namespace std;
using namespace sf;


int main()
{
	// randomize init
	srand(static_cast<unsigned int> (time(NULL)));

	RenderWindow window(sf::VideoMode(1024, 768), "TetroRythm");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	Image icon;
	icon.loadFromFile("Images/logo.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	MasterClass gameMC(window);
	gameMC.run();
	return 0;
}


