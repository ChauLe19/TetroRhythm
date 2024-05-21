#pragma once
extern std::string importedPath;
#ifndef ENUMS_H
#define ENUMS_H
#include <iostream>
#include <boost/bimap.hpp>
#include <boost/assign.hpp>
#include "Board.h"

enum class State {
	MENU, GAME, GAME_OPTIONS, MAP_EDITOR,
	SETTINGS, GAMEOVER, PAUSE, MAP_EDITOR_SELECT
};

enum class Controls_Key {
	/*HOLD,*/ HARD_DROP, HARD_DROP_ALT, GRAVITY, SIZE
};

enum class HitType {
	HIT, ALMOST, MISS, INVALID
};

const boost::bimap<Controls_Key, std::string> controlsKeyStringMap = boost::assign::list_of<boost::bimap<Controls_Key, std::string>::relation>
//	(Controls_Key::HOLD, "HOLD")
	(Controls_Key::HARD_DROP, "HARD_DROP")
	(Controls_Key::HARD_DROP_ALT, "HARD_DROP_ALT")
	(Controls_Key::GRAVITY, "GRAVITY");

const std::map<ClearType, std::string> clearTypeStringMap = {
	{ClearType::NONE, "None"},
	{ClearType::SINGLE, "Single"},
	{ClearType:: DOUBLE, "Double"},
	{ClearType::TRIPLE, "Triple"},
	{ClearType::TETRIS, "Tetris"},
	{ClearType::TSPIN_MINI_NO, "T-Spin Mini"},
	{ClearType::TSPIN_NO, "T-Spin"},
	{ClearType::TSPIN_MINI_SINGLE, "T-Spin Mini Single"},
	{ClearType::TSPIN_SINGLE, "T-Spin Single"},
	{ClearType::TSPIN_MINI_DOUBLE, "T-Spin Mini Double"},
	{ClearType::TSPIN_DOUBLE, "T-Spin Double"},
	{ClearType::TSPIN_TRIPLE, "T-Spin Triple"},
	{ClearType::COMBO, "Combo"},
	{ClearType::SOFTDROP, "Soft Drop"},
	{ClearType::HARDDROP, "Dard Drop"},
	{ClearType::SINGLE_LINE_PC, "Single-Line PC"},
	{ClearType::DOUBLE_LINE_PC, "Double-Line PC"},
	{ClearType::TRIPLE_LINE_PC, "Triple-Line PC"},
	{ClearType::TETRIS_PC, "Tetris PC"},
	{ClearType::B2B_TETRIS_PC, "B2B Tetris PC"},
	{ClearType::B2B_TETRIS, "B2B Tetris"},
	{ClearType::B2B_TSPIN_MINI_SINGLE, "B2B T-Spin Mini Single"},
	{ClearType::B2B_TSPIN_SINGLE, "B2B T-Spin Single"},
	{ClearType::B2B_TSPIN_MINI_DOUBLE, "B2B T-Spin Mini Double"},
	{ClearType::B2B_TSPIN_DOUBLE, "B2B T-Spin Double"},
	{ClearType::B2B_TSPIN_TRIPLE, "B2B T-Spin Triple"},
	{ClearType::B2B_PENTRIS_PC, "B2B Pentris PC"},
	{ClearType::B2B_PENTRIS, "B2B Pentris"},
	{ClearType::PENTRIS, "Pentris"}
};

const std::map<Controls_Key, std::string> controlsStringMap = {
//	{Controls_Key::HOLD, "Hold"},
	{Controls_Key::HARD_DROP, "Hard drop"},
	{Controls_Key::HARD_DROP_ALT, "Hard drop alt"},
	{Controls_Key::GRAVITY, "Gravity"},
};

const std::map<sf::Keyboard::Key, std::string> keyboardKeyStringMap = {
	{sf::Keyboard::A, "A"},
	{sf::Keyboard::B, "B"},
	{sf::Keyboard::C, "C"},
	{sf::Keyboard::D, "D"},
	{sf::Keyboard::E, "E"},
	{sf::Keyboard::F, "F"},
	{sf::Keyboard::G, "G"},
	{sf::Keyboard::H, "H"},
	{sf::Keyboard::I, "I"},
	{sf::Keyboard::J, "J"},
	{sf::Keyboard::K, "K"},
	{sf::Keyboard::L, "L"},
	{sf::Keyboard::M, "M"},
	{sf::Keyboard::N, "N"},
	{sf::Keyboard::O, "O"},
	{sf::Keyboard::P, "P"},
	{sf::Keyboard::Q, "Q"},
	{sf::Keyboard::R, "R"},
	{sf::Keyboard::S, "S"},
	{sf::Keyboard::T, "T"},
	{sf::Keyboard::U, "U"},
	{sf::Keyboard::V, "V"},
	{sf::Keyboard::W, "W"},
	{sf::Keyboard::X, "X"},
	{sf::Keyboard::Y, "Y"},
	{sf::Keyboard::Z, "Z"},
	{sf::Keyboard::Num0, "Num0"},
	{sf::Keyboard::Num1, "Num1"},
	{sf::Keyboard::Num2, "Num2"},
	{sf::Keyboard::Num3, "Num3"},
	{sf::Keyboard::Num4, "Num4"},
	{sf::Keyboard::Num5, "Num5"},
	{sf::Keyboard::Num6, "Num6"},
	{sf::Keyboard::Num7, "Num7"},
	{sf::Keyboard::Num8, "Num8"},
	{sf::Keyboard::Num9, "Num9"},
	{sf::Keyboard::Escape, "Escape"},
	{sf::Keyboard::LControl, "LControl"},
	{sf::Keyboard::LShift, "LShift"},
	{sf::Keyboard::LAlt, "LAlt"},
	{sf::Keyboard::LSystem, "LSystem"},
	{sf::Keyboard::RControl, "RControl"},
	{sf::Keyboard::RShift, "RShift"},
	{sf::Keyboard::RAlt, "RAlt"},
	{sf::Keyboard::RSystem, "RSystem"},
	{sf::Keyboard::Menu, "Menu"},
	{sf::Keyboard::LBracket, "LBracket"},
	{sf::Keyboard::RBracket, "RBracket"},
	{sf::Keyboard::SemiColon, "SemiColon"},
	{sf::Keyboard::Comma, "Comma"},
	{sf::Keyboard::Period, "Period"},
	{sf::Keyboard::Quote, "Quote"},
	{sf::Keyboard::Slash, "Slash"},
	{sf::Keyboard::BackSlash, "BackSlash"},
	{sf::Keyboard::Tilde, "Tilde"},
	{sf::Keyboard::Equal, "Equal"},
	{sf::Keyboard::Dash, "Dash"},
	{sf::Keyboard::Space, "Space"},
	{sf::Keyboard::Return, "Return"},
	{sf::Keyboard::BackSpace, "BackSpace"},
	{sf::Keyboard::Tab, "Tab"},
	{sf::Keyboard::PageUp, "PageUp"},
	{sf::Keyboard::PageDown, "PageDown"},
	{sf::Keyboard::End, "End"},
	{sf::Keyboard::Home, "Home"},
	{sf::Keyboard::Insert, "Insert"},
	{sf::Keyboard::Delete, "Delete"},
	{sf::Keyboard::Add, "Add"},
	{sf::Keyboard::Subtract, "Subtract"},
	{sf::Keyboard::Multiply, "Multiply"},
	{sf::Keyboard::Divide, "Divide"},
	{sf::Keyboard::Left, "Left"},
	{sf::Keyboard::Right, "Right"},
	{sf::Keyboard::Up, "Up"},
	{sf::Keyboard::Down, "Down"},
	{sf::Keyboard::Numpad0, "Numpad0"},
	{sf::Keyboard::Numpad1, "Numpad1"},
	{sf::Keyboard::Numpad2, "Numpad2"},
	{sf::Keyboard::Numpad3, "Numpad3"},
	{sf::Keyboard::Numpad4, "Numpad4"},
	{sf::Keyboard::Numpad5, "Numpad5"},
	{sf::Keyboard::Numpad6, "Numpad6"},
	{sf::Keyboard::Numpad7, "Numpad7"},
	{sf::Keyboard::Numpad8, "Numpad8"},
	{sf::Keyboard::Numpad9, "Numpad9"},
	{sf::Keyboard::F1, "F1"},
	{sf::Keyboard::F2, "F2"},
	{sf::Keyboard::F3, "F3"},
	{sf::Keyboard::F4, "F4"},
	{sf::Keyboard::F5, "F5"},
	{sf::Keyboard::F6, "F6"},
	{sf::Keyboard::F7, "F7"},
	{sf::Keyboard::F8, "F8"},
	{sf::Keyboard::F9, "F9"},
	{sf::Keyboard::F10, "F10"},
	{sf::Keyboard::F11, "F11"},
	{sf::Keyboard::F12, "F12"},
	{sf::Keyboard::F13, "F13"},
	{sf::Keyboard::F14, "F14"},
	{sf::Keyboard::F15, "F15"},
	{sf::Keyboard::Pause, "Pause"},
	{sf::Keyboard::KeyCount, "KeyCount"},
};


const std::array<std::array<std::array<short, boardWidth>, boardHeight>, 42> infBoardSimulation = { {
	{{
		{{0, 0, 0, 0 ,0, 0}},
		{{0, 0, 0, 0 ,0, 0}},
		{{0, 0, 0, 0 ,0, 0}},
		{{0, 0, 0, 0 ,0, 0}},
		{{0, 0, 0, 0 ,0, 0}},
		{{0, 0, 0, 0 ,0, 0}}
	}},
	{ {
		{ {0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{6, 0, 0, 0, 0, 0 }},
		{{6, 6, 6, 0, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{6, 0, 0, 0, 7, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{1, 1, 0, 0, 0, 0 }},
		{{6, 1, 1, 0, 7, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 4, 0, 0, 0 }},
		{{1, 1, 4, 4, 0, 0 }},
		{{6, 1, 1, 4, 7, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 0, 0, 0, 0, 0 }},
		{{2, 0, 0, 0, 0, 0 }},
		{{2, 2, 4, 0, 0, 0 }},
		{{1, 1, 4, 4, 0, 0 }},
		{{6, 1, 1, 4, 7, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 3, 3, 0, 0, 0 }},
		{{2, 3, 3, 0, 0, 0 }},
		{{2, 2, 4, 0, 0, 0 }},
		{{1, 1, 4, 4, 0, 0 }},
		{{6, 1, 1, 4, 7, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 3, 3, 0, 0, 0 }},
		{{2, 3, 3, 0, 0, 5 }},
		{{2, 2, 4, 0, 0, 5 }},
		{{1, 1, 4, 4, 0, 5 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 3, 3, 0, 0, 0 }},
		{{2, 3, 3, 4, 0, 5 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{1, 1, 0, 0, 0, 0 }},
		{{0, 1, 1, 0, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 1, 1, 0, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 2, 2, 0, 0, 0 }},
		{{2, 1, 1, 0, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 2, 2, 0, 3, 3 }},
		{{2, 1, 1, 0, 3, 3 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 6, 6, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{3, 3, 0, 0, 0, 0 }},
		{{3, 3, 0, 6, 6, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 4, 0 }},
		{{3, 3, 0, 0, 4, 4 }},
		{{3, 3, 0, 6, 6, 4 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 1, 4, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 6, 6, 6 }},
		{{0, 0, 0, 1, 4, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{2, 0, 0, 1, 4, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 7, 0, 0, 0, 0 }},
		{{7, 7, 0, 0, 0, 0 }},
		{{2, 7, 0, 1, 4, 6 }}
	}},
	{{
		{{5, 0, 0, 0, 0, 0 }},
		{{5, 0, 0, 0, 0, 0 }},
		{{5, 0, 0, 0, 0, 0 }},
		{{5, 7, 0, 0, 0, 0 }},
		{{7, 7, 0, 0, 0, 0 }},
		{{2, 7, 0, 1, 4, 6 }}
	}},
	{{
		{{5, 2, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 0 }},
		{{5, 2, 2, 0, 0, 0 }},
		{{5, 7, 0, 0, 0, 0 }},
		{{7, 7, 0, 0, 0, 0 }},
		{{2, 7, 0, 1, 4, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 0 }},
		{{5, 2, 2, 0, 0, 0 }},
		{{5, 7, 6, 6, 0, 0 }},
		{{7, 7, 6, 0, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 0 }},
		{{5, 2, 2, 0, 0, 0 }},
		{{7, 7, 6, 4, 4, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 5 }},
		{{5, 2, 0, 0, 0, 5 }},
		{{5, 2, 2, 0, 0, 5 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 5 }},
		{{5, 2, 1, 1, 0, 5 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{3, 3, 0, 0, 0, 0 }},
		{{3, 3, 0, 0, 0, 0 }},
		{{5, 2, 0, 0, 0, 5 }},
		{{5, 2, 1, 1, 0, 5 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{3, 3, 0, 0, 0, 0 }},
		{{3, 3, 0, 7, 0, 0 }},
		{{5, 2, 1, 1, 0, 5 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{3, 3, 0, 0, 0, 1 }},
		{{3, 3, 0, 7, 1, 1 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 5, 0, 0, 0 }},
		{{0, 0, 5, 0, 0, 0 }},
		{{3, 3, 5, 0, 0, 1 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 5, 0, 0, 0 }},
		{{0, 0, 5, 3, 3, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 5, 6, 6, 6 }},
		{{0, 0, 5, 3, 3, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 2 }},
		{{0, 0, 0, 2, 2, 2 }},
		{{0, 0, 5, 6, 6, 6 }},
		{{0, 0, 5, 3, 3, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 4, 4 }},
		{{0, 0, 0, 4, 4, 2 }},
		{{0, 0, 0, 2, 2, 2 }},
		{{0, 0, 5, 6, 6, 6 }},
		{{0, 0, 5, 3, 3, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 4, 4 }},
		{{0, 0, 0, 4, 4, 2 }},
		{{0, 7, 0, 2, 2, 2 }},
		{{0, 7, 5, 3, 3, 6 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{5, 0, 0, 0, 4, 4 }},
		{{5, 0, 0, 4, 4, 2 }},
		{{5, 7, 0, 2, 2, 2 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{4, 0, 0, 0, 0, 0 }},
		{{4, 4, 0, 0, 0, 0 }},
		{{5, 4, 0, 0, 4, 4 }},
		{{5, 0, 0, 4, 4, 2 }},
		{{5, 7, 0, 2, 2, 2 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{4, 0, 0, 0, 0, 0 }},
		{{4, 4, 6, 0, 0, 0 }},
		{{5, 4, 6, 0, 4, 4 }},
		{{5, 7, 0, 2, 2, 2 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{4, 0, 0, 0, 0, 0 }},
		{{5, 7, 0, 2, 2, 2 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 1, 0, 0 }},
		{{4, 0, 1, 1, 0, 0 }}
	}},
	{{
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{0, 0, 0, 0, 0, 0 }},
		{{7, 7, 7, 1, 0, 0 }},
		{{4, 7, 1, 1, 0, 0 }}
	}}
}};

const std::array<std::array<std::array<short, boardWidth>, boardHeight>, 19> tutorialBoards = { {
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 0, 0, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 0, 0, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 0, 0, 0, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 0, 0, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 0, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 0, 0, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 0, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 0, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 0, 0, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 0, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 0, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}},
	{{
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 0, 0, 0, 0, 8}},
		{{8, 8, 8, 8, 8, 8}},
		{{8, 8, 8, 8, 8, 8}}
	}}
}};

#endif