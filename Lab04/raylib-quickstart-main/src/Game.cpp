#include "Game.h"

void Game::Init()
{
	world.Setup();
}

void Game::Draw()
{
	world.Draw();
}

void Game::Update()
{
	world.Update();
}
