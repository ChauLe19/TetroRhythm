// TetroRythm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Game.h"
#include "Board.h"
#include "Tetromino.h"
using namespace std;
using namespace sf;


int main()
{

	RenderWindow window(sf::VideoMode(1024, 768), "TetroRythm");
	Board board(100, 100);
	srand(time(NULL));


	 Tetromino* currentPiecePtr = new Tetromino(static_cast<Type>(rand() % 7));
	 Tetromino currentPiece = *currentPiecePtr;
	 while (window.isOpen())
	 {
		 Event event;
		 while (window.pollEvent(event))
		 {
			 if (event.type == Event::Closed)
				 window.close();
			 if (event.type == Event::KeyPressed)
			 {
				 switch (event.key.code)
				 {
				 case Keyboard::F:
					 currentPiece.rotate(Rotational_Direction::CW, board);
					 break;
				 case Keyboard::A:
					 currentPiece.rotate(Rotational_Direction::CCW, board);
					 break;
				 case Keyboard::S:
					 currentPiece.rotate(Rotational_Direction::R180, board);
					 break;
				 case Keyboard::L:
					 currentPiece.move(Moving_Direction::RIGHT_DIR, board);
					 break;
				 case Keyboard::J:
					 currentPiece.move(Moving_Direction::LEFT_DIR, board);
					 break;
				 case Keyboard::K:
					 currentPiece.move(Moving_Direction::DOWN_DIR, board);
					 break;
				 case Keyboard::I:
					 currentPiece.hardDrop(board);
					 //currentPiece = nextPiece();
					 currentPiecePtr = new Tetromino(static_cast<Type>(rand() % 7));
					 currentPiece = *currentPiecePtr;
					 break;
				 }
				 board.clearLines();
			 }
		 }

		 window.clear(Color::White);
		 //window.draw(bgSprite);
		 board.render(window);
		 currentPiece.render(window, board);
		 window.display();
	 }
	//Game game;
	//game.run(window);

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
