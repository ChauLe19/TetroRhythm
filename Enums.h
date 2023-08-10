#pragma once
extern std::string importedPath;
#ifndef ENUMS_H
#define ENUMS_H
#include <iostream>
#include "Board.h"

enum class State {
	MENU, GAME, GAME_OPTIONS, MAP_EDITOR,
	SETTINGS, GAMEOVER, PAUSE, MAP_EDITOR_SELECT
};

enum class Controls_Key {
	MOVE_LEFT = 0, MOVE_RIGHT, ROTATE_CCW, ROTATE_CW,
	ROTATE_180, HOLD, HARD_DROP, SOFT_DROP
};

const map<ClearType, string> clearTypeStringMap = {
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

#endif