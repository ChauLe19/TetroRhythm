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
	Button helpButton = Button(Color::White, 50, Color::Transparent, "?", Vector2f(2048 - 40 - 10, 10), Vector2f(40, 40), Color(0, 186, 211), Keyboard::A);
	Button blankPopup = Button(Color::White, 50, Color(0,0,0,230), "", Vector2f(200, 100), Vector2f(2048-400, 1152 - 200), Color::Transparent, Keyboard::Unknown);
	Text text;
	Sprite instructionSprite;
	Board board = Board(boardX, boardY);
	bool keyMouseRegistered = false;
	bool keyMouseReleased = false;
	VertexArray inputVertex = VertexArray(PrimitiveType::Quads);
	Vector2i lastMousePos = Vector2i(0,0);
	Tetromino currentPiecePtr = Tetromino(Type::S);
	SoundBuffer sfxBuffer;
	Sound sfx;
	array<Tetromino, 19> bag = {
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

	void drawInstructionPopup(RenderWindow& window);
public:
	Tutorial(StateManager &stateManager);
	~Tutorial();

	// StateScreen functions
	//****************************************************
	void tick(const float & dt, RenderWindow& window);
	void render(RenderWindow& window);
	void keyEvent(const float & dt, Event event);
	void mouseEvent(const float & dt, RenderWindow& window, Event event);

};

