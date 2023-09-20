#include "Tutorial.h"
#include "Utils.h"
#include "Menu.h"
#include "GameSettings.h"

Tutorial::Tutorial(StateManager& stateManager) : StateScreen(stateManager)
{
	text.setFont(assetManager->getFont("game font"));
	text.setFillColor(Color::White);

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

void Tutorial::tick(const float& dt, RenderWindow& window)
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

void Tutorial::render(RenderWindow& window)
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
	helpButton.render(window, text);

	text.setFillColor(Color::White);
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
		blankPopup.render(window, text);
		helpButton.setHighlight(true);
		instructionSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		window.draw(instructionSprite);
	}
	else
	{
		helpButton.setHighlight(false);
	}

}

void Tutorial::keyEvent(const float& dt, Event event)
{
}

void Tutorial::mouseEvent(const float& dt, RenderWindow& window, Event event)
{
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

void Tutorial::drawInstructionPopup(RenderWindow& window)
{

}

