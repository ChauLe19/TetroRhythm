#pragma once
#include "StateScreen.h"
#include "Button.h"
#include "Board.h"
#include "GameBase.h"
#include "GameSettings.h"

class Tutorial :
    public StateScreen
{
private:
	Button helpButton = Button(sf::Text("?", getAssetManager()->getFont("game font"), 50U));
	Button blankPopup = Button(sf::Text("", getAssetManager()->getFont("game font"), 50U));
	sf::Text text;
	sf::Sprite instructionSprite;
	Board board = Board(boardX, boardY);
	bool keyMouseRegistered = false;
	bool keyMouseReleased = false;
	sf::VertexArray inputVertex = sf::VertexArray(sf::PrimitiveType::Quads);
	sf::Vector2i lastMousePos = sf::Vector2i(0,0);
	Tetromino currentPiecePtr = Tetromino(Type::S);
	sf::SoundBuffer sfxBuffer;
	sf::Sound sfx;
	std::array<Tetromino, 19> bag = {
		Tetromino(Type::S),
		Tetromino(Type::S),
		Tetromino(Type::Z),
		Tetromino(Type::Z),
		Tetromino(Type::J),
		Tetromino(Type::J),
		Tetromino(Type::J),
		Tetromino(Type::J),
		Tetromino(Type::L),
		Tetromino(Type::L),
		Tetromino(Type::L),
		Tetromino(Type::L),
		Tetromino(Type::T),
		Tetromino(Type::T),
		Tetromino(Type::T),
		Tetromino(Type::T),
		Tetromino(Type::O),
		Tetromino(Type::I),
		Tetromino(Type::I),
	};
	bool locked = false;
	int counter = 0;
	bool tutorialOver = false;
	int stageRender = 0;

	void drawInstructionPopup(sf::RenderWindow& window);
public:
	Tutorial(StateManager &stateManager);
	~Tutorial();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void keyEvent(const float & dt, sf::Event event);
	void mouseEvent(const float & dt, sf::RenderWindow& window, sf::Event event);

};

