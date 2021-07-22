#pragma once
#include "GameBase.h"
class AutoDropGame :
	public GameBase
{
public:
	void tick(RenderWindow& window, int& frameCount);
	void dropOnBeat();
};

