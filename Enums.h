extern std::string importedPath;
#ifndef ENUMS_H
#define ENUMS_H
#include <iostream>
enum class State {
	MENU, GAME, GAME_OPTIONS, MAP_EDITOR,
	SETTINGS, GAMEOVER, PAUSE, MAP_EDITOR_SELECT
};

enum class Controls_Key {
	MOVE_LEFT = 0, MOVE_RIGHT, ROTATE_CCW, ROTATE_CW,
	ROTATE_180, HOLD, HARD_DROP, SOFT_DROP
};
#endif