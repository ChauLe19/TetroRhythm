#include "Game.h"

Game::Game()
{
	cout << "Initializing game" << endl;
	//board = Board(boardX, boardY);
	/*bag.insert(bag.end(), allPieces.begin(), allPieces.end());
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(bag.begin(), bag.end(), default_random_engine(seed));
	bag.insert(bag.end(), allPieces.begin(), allPieces.end());
	list<Tetromino>::iterator it = bag.begin();
	advance(it, 7);
	shuffle(it, bag.end(), default_random_engine(seed));*/
	currentPiece = Tetromino(static_cast<Type>(rand() % 7));
	//holdPiece = Tetromino(static_cast<Type>(rand() % 7));

}

Tetromino& Game::nextPiece()
{
	//currentPiece = bag.front();
	//bag.pop_front();

	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//if (bag.size() <= 7)
	//{
	//	for (int i = 0; i < 7; i++)
	//	{
	//		bag.push_back(Tetromino(allPieces[i])); // append all 7 pieces to he bag
	//	}
	//}
	//list<Tetromino>::iterator it = bag.begin();
	//advance(it, 7);
	//shuffle(it, bag.end(), default_random_engine(seed));

	return currentPiece;
}

void Game::run(RenderWindow& window)
{
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
					currentPiece = Tetromino(static_cast<Type>(rand() % 7));
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
}

Game::~Game()
{
}

