#ifndef ENUMS_H
#define ENUMS_H
enum class State { MENU, GAME, SETTINGS, GAMEOVER, PAUSE };
enum class Controls_Key {
	MOVE_LEFT = 0, MOVE_RIGHT, ROTATE_CCW, ROTATE_CW,
	ROTATE_180, HOLD, HARD_DROP, SOFT_DROP
};
#endif