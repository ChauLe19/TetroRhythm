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
	Button helpButton = Button(sf::Color::White, 50, sf::Color::Transparent, "?", sf::Vector2f(2048 - 40 - 10, 10), sf::Vector2f(40, 40), sf::Color(0, 186, 211), sf::Keyboard::A);
	Button blankPopup = Button(sf::Color::White, 50, sf::Color(0,0,0,230), "", sf::Vector2f(200, 100), sf::Vector2f(2048-400, 1152 - 200), sf::Color::Transparent, sf::Keyboard::Unknown);
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

