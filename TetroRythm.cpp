// TetroRythm.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Initilize Masterclass and window. Start game

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "GameBase.h"
#include "MasterClass.h"

using namespace std;
using namespace sf;

int main()
{

	// randomize init
	srand(static_cast<unsigned int> (time(NULL)));



	RenderWindow window(sf::VideoMode(2048, 1152), "TetroRythm", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::View view(FloatRect(0.f,0.f, 2048.f, 1152.f));
	window.setView(view);

	Image icon;
	icon.loadFromFile("Images/logo.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	MasterClass gameMC(window);
	gameMC.run();
	return 0;
}


