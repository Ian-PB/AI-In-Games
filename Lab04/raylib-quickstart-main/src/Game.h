#pragma once
#include "raylib.h"
#include "World.h"

class Game
{
public:
	void Init();
	void Draw();
	void Update();

private:
	World world;
};

