#include "World.h"
#include <raymath.h>

void World::Setup()
{
	amountOfCells = cells.WIDTH * cells.HEIGHT;
	cellSize = GetScreenWidth() / (float)cells.WIDTH;

	// Set positions
	for (int x = 0; x < cells.WIDTH; x++)
	{
		for (int y = 0; y < cells.HEIGHT; y++)
		{
			Vector2 cellPos = { x * cellSize, y * cellSize };

			int i = World::GetIndex(x, y, GetWidth());
			cells.positions[i] = cellPos;
		}
	}
}

void World::Draw()
{
	for (int i = 0; i < amountOfCells; i++)
	{
		Color cellColor = BLUE;
		if (i % 2 == 0)
			cellColor = DARKBLUE;

		DrawRectangle(cells.positions[i].x, cells.positions[i].y, cellSize, cellSize, cellColor);
		DrawRectangleLines(cells.positions[i].x, cells.positions[i].y, cellSize, cellSize, RAYWHITE);
	}
}

void World::Update()
{
	// Set start
	if (IsMouseButtonReleased(0))
	{
		Vector2 mousePos = GetMousePosition();

		for (int i = 0; i < cells.WIDTH; i++)
		{
			Vector2 cellBoundsMin;
			Vector2 cellBoundsMax;
			cellBoundsMin = cells.positions[i];
			cellBoundsMax = { cells.positions[i].x + cellSize, cells.positions[i].y + cellSize };
		}
	}
	// Set end
	else if (IsMouseButtonReleased(1))
	{

	}
}
