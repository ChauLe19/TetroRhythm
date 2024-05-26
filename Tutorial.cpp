#include "Tutorial.h"
#include "Utils.h"
#include "Menu.h"
#include "GameSettings.h"
#include "Styles.h"

Tutorial::Tutorial(StateManager& stateManager) : StateScreen(stateManager)
{
	using namespace std;
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(sf::Color::White);

	helpButton.setPosition(sf::Vector2f(2048 - 40 - 10, 10));
	helpButton.setSize(sf::Vector2f(40, 40));
	helpButton.setHighlightColor(TRStyles::btnHLColor);
	helpButton.setBaseColor(TRStyles::btnBaseColor);

	blankPopup.setFillColor(sf::Color(0, 0, 0, 230));
	blankPopup.setBaseColor(sf::Color::White);
	blankPopup.setHighlightColor(sf::Color::Transparent);
	blankPopup.setSize(sf::Vector2f(2048 - 400, 1152 - 200));
	blankPopup.setPosition(sf::Vector2f(200, 100));

	instructionSprite.setTexture(AssetManager::getInstance()->getTexture("instruction"));
	instructionSprite.setOrigin(instructionSprite.getLocalBounds().width / 2.0f, instructionSprite.getLocalBounds().height / 2.0f);

	currentPiecePtr = bag.at(counter);
	board.setBoard(tutorialBoards.at(counter));

	if (!sfxBuffer.loadFromFile("SFX/drop.ogg"))
	{
		cerr << "Unable to open file drop.ogg" << endl;
	}
	sfx.setBuffer(sfxBuffer);
	sfx.setVolume(GameSettings::getInstance()->getSettings()->sfx);
}

Tutorial::~Tutorial()
{
}

void Tutorial::tick(const float& dt, sf::RenderWindow& window)
{
	if (stageRender > 0)
	{
		stageRender--;
		if (stageRender == 0) // move to the next piece (stage of the tutorial)
		{
			counter++;
			if (counter < bag.size())
			{
				currentPiecePtr = bag.at(counter);
				board.setBoard(tutorialBoards.at(counter));
			}
			else
			{
				tutorialOver = true;
			}
		}
	}
}

void Tutorial::render(sf::RenderWindow& window)
{
	text.setCharacterSize(100);
	text.setString("How to play");
	text.setPosition(boardX + boardWidth * boardSquareSize/2 - text.getLocalBounds().width/2, 20);
	window.draw(text);


	if (mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		window.draw(assetManager->getDrawable("back button hl"));
	}
	else
	{
		window.draw(assetManager->getDrawable("back button"));
	}
	window.draw(helpButton);

	text.setFillColor(sf::Color::White);
	if (tutorialOver)
	{
		text.setCharacterSize(100);
		text.setString("Congratulation!\nYou have finished the tutorial");
		text.setPosition(boardX + boardWidth * boardSquareSize/2 - text.getLocalBounds().width/2, 300);
		window.draw(text);
		return;
	}

	text.setCharacterSize(50);
	text.setString("Place pieces correctly on the board by drawing on the board.");
	text.setPosition(boardX + boardWidth * boardSquareSize/2 - text.getLocalBounds().width/2, boardY + boardSquareSize * boardHeight + 20);
	window.draw(text);
	text.setCharacterSize(50);
	text.setString("Hover over the help button for directions.");
	text.setPosition(boardX + boardWidth * boardSquareSize/2 - text.getLocalBounds().width/2, boardY + boardSquareSize * boardHeight + 70);
	window.draw(text);

	board.render(window);
	currentPiecePtr.render(window, boardX + (boardSquareSize/ 2) + boardSquareSize* boardWidth + 10, boardY + boardSquareSize / 2+ boardSquareSize* 2);
	window.draw(inputVertex);

	if (stageRender > 0)
	{
		text.setCharacterSize(100);
		text.setString("Nice");
		text.setPosition(boardX + boardWidth * boardSquareSize/2 - text.getLocalBounds().width/2, 300);
		window.draw(text);
	}
	
	if (helpButton.mouseInButton(window))
	{
		window.draw(blankPopup);
		instructionSprite.setPosition(window.getView().getSize().x / 2, window.getView().getSize().y / 2);
		window.draw(instructionSprite);
	}

}

void Tutorial::keyEvent(const float& dt, sf::Event event)
{
}

void Tutorial::mouseEvent(const float& dt, sf::RenderWindow& window, sf::Event event)
{
	using namespace sf;
	using namespace std;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && mouseInBox(window, 20, 20, 40, 40)) // back button
	{
		stateManager.addState(std::unique_ptr<StateScreen>(new Menu(stateManager)));
		return;
	}

	if (tutorialOver)
	{

	}
	else
	{
		if (keyMouseRegistered == true || event.type == sf::Event::MouseButtonPressed)
		{
			locked = true;
			keyMouseRegistered = false;
			lastMousePos = (Mouse::getPosition(window));
		}

		if (keyMouseReleased == true || event.type == sf::Event::MouseButtonReleased)
		{
			keyMouseReleased = false;
			locked = false; // Reset
			if (inputVertex.getVertexCount() >= 2)
			{

				Vertex firstPoint = inputVertex[0];
				Vertex lastPoint = inputVertex[inputVertex.getVertexCount() - 1];
				int xDir = lastPoint.position.x - firstPoint.position.x;
				int yDir = lastPoint.position.y - firstPoint.position.y;
				Moving_Direction mouseDirection = Moving_Direction::UP_DIR;
				
				int XorYdir = max(abs(xDir), abs(yDir));
				if (XorYdir >= 50) // only register input if it's long enough
				{
					if (XorYdir == abs(xDir))// favor x direction
					{
						if (xDir > 0) // mouse move right
						{
							mouseDirection = Moving_Direction::RIGHT_DIR;
						}
						else if (xDir < 0)
						{
							mouseDirection = Moving_Direction::LEFT_DIR;
						}
					}
					else // favor y direction
					{
						if (yDir > 0)
						{
							mouseDirection = Moving_Direction::DOWN_DIR;
						}
						else if (yDir < 0)
						{
							mouseDirection = Moving_Direction::UP_DIR;
						}
					}

					int minX = -currentPiecePtr.getMinX();
					int minY = -currentPiecePtr.getMinY();
					int maxX = 9 - currentPiecePtr.getMaxX();
					int maxY = 9 - currentPiecePtr.getMaxY();
					// x - 1, y - 1 to offset to center of the piece
					int x = std::floor((firstPoint.position.x - boardX) / boardSquareSize);
					int y = std::floor((firstPoint.position.y - boardY) / boardSquareSize);


					bool possible = currentPiecePtr.setPiece(x, y, mouseDirection, board);

					if (possible) // if set piece sucessfully, move to next piece
					{
						sfx.stop();
						sfx.play();
						stageRender = 60;
						cout << "success" << endl;
					}
				}
			}
			inputVertex.clear();
		}
		
		if (locked)
		{
			if (lastMousePos != sf::Mouse::getPosition(window)) // When the Mouse hasn't moved don't add any new Vertex (save memory)
			{
				Vector2f prevMouseViewPos = window.mapPixelToCoords(lastMousePos);
				Vector2i currentMousePos = Mouse::getPosition(window);
				Vector2f mouseViewPos = window.mapPixelToCoords(currentMousePos);

				sf::Vector2f direction = mouseViewPos - prevMouseViewPos;
				sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
				sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

				sf::Vector2f offset = (inputThickness / 2.f) * unitPerpendicular;

				inputVertex.append(prevMouseViewPos + offset);
				inputVertex.append(mouseViewPos + offset);
				inputVertex.append(mouseViewPos - offset);
				inputVertex.append(prevMouseViewPos - offset);

				lastMousePos = currentMousePos;
			}
		}
	}

}

void Tutorial::drawInstructionPopup(sf::RenderWindow& window)
{

}

