#pragma once
#include "GameBase.h"
class DropToTheBeatGame :
    public GameBase
{
public:
	void tick(RenderWindow& window, int& frameCount);
	void dropOnBeat();
};

