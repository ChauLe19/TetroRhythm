#include "Game.h"

Game::Game()
{
	cout << "Initializing game" << endl;
	//board = Board(boardX, boardY);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// add 2 initial 7-bags
	for (int j = 0; j < 2; j++)
	{
		vector<Type> tempTypeVector = allPieces;
		shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}

	currentPiecePtr = &nextPiece();

}

void Game::hold()
{
	if (!alreadyHold)
	{
		if (holdPiecePtr == nullptr)
		{
			holdPiecePtr = currentPiecePtr;
			currentPiecePtr = &nextPiece();
		}
		else
		{
			Tetromino* tempPiecePtr = holdPiecePtr;
			holdPiecePtr = currentPiecePtr;
			currentPiecePtr = tempPiecePtr;
		}
		holdPiecePtr->reset();
		alreadyHold = true;
	}
}

Tetromino& Game::nextPiece()
{
	currentPiecePtr = bag.front();
	bag.pop_front();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if (bag.size() <= 7)
	{
		vector<Type> tempTypeVector = allPieces;
		shuffle(tempTypeVector.begin(), tempTypeVector.end(), default_random_engine(seed));

		while (!tempTypeVector.empty())
		{
			Type tempType = tempTypeVector.back();
			tempTypeVector.pop_back();
			bag.push_back(new Tetromino(tempType)); // append all 7 pieces to he bag
		}
	}
	cout << endl;


	return *currentPiecePtr;
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
					currentPiecePtr->rotate(Rotational_Direction::CW, board);
					break;
				case Keyboard::A:
					currentPiecePtr->rotate(Rotational_Direction::CCW, board);
					break;
				case Keyboard::S:
					currentPiecePtr->rotate(Rotational_Direction::R180, board);
					break;
				case Keyboard::L:
					currentPiecePtr->move(Moving_Direction::RIGHT_DIR, board);
					break;
				case Keyboard::J:
					currentPiecePtr->move(Moving_Direction::LEFT_DIR, board);
					break;
				case Keyboard::K:
					currentPiecePtr->move(Moving_Direction::DOWN_DIR, board);
					break;
				case Keyboard::I:
					currentPiecePtr->hardDrop(board);
					//currentPiece = nextPiece();
					currentPiecePtr = &nextPiece();
					alreadyHold = false;
					break;
				case Keyboard::D:
					hold();
					break;
				}
				board.clearLines();
			}
		}

		window.clear(Color::Black);
		//window.draw(bgSprite);
		board.render(window);
		currentPiecePtr->render(window, board);
		if (holdPiecePtr != nullptr)
			holdPiecePtr->render(window, 50, 100);
		int counter = 0;
		std::list<Tetromino*>::iterator fifthIt = bag.begin();
		advance(fifthIt, 5);
		for (std::list<Tetromino*>::iterator it = bag.begin(); it != fifthIt; ++it)
		{
			(*it)->render(window, 300, 100 + 50 * counter);
			counter++;
		}
		window.display();
	}
}

Game::~Game()
{
	delete currentPiecePtr;
	delete holdPiecePtr;
}

