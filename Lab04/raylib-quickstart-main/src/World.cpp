#include "World.h"
#include <raymath.h>
#include <iostream>
#include <string>

void World::Setup()
{
	amountOfCells = cells.WIDTH * cells.HEIGHT;
	float worldSizeX = GetScreenWidth();
	cellSize = worldSizeX / (float)cells.WIDTH;

	// Set positions
	for (int x = 0; x < cells.WIDTH; x++)
	{
		for (int y = 0; y < cells.HEIGHT; y++)
		{
			Vector2 cellPos = { x * cellSize, y * cellSize };

			int i = World::GetIndex(x, y, cells.WIDTH);
			cells.positions[i] = cellPos;
			cells.color[i] = BASE_COLOR;
		}
	}

	ResetCosts();
}

void World::Draw()
{
	for (int i = 0; i < amountOfCells; i++)
	{
		DrawRectangle(cells.positions[i].x, cells.positions[i].y, cellSize, cellSize, cells.color[i]);
		DrawRectangleLines(cells.positions[i].x, cells.positions[i].y, cellSize, cellSize, BLACK);


		switch (displayType)
		{
		case DisplayType::None:
			break;

		case DisplayType::Costs:
			DrawText(std::to_string(cells.costs[i]).c_str(), cells.positions[i].x, cells.positions[i].y, cellSize / 2, BLACK);
			break;

		case DisplayType::Heuristics:
			DrawText(std::to_string(cells.heuristics[i]).c_str(), cells.positions[i].x, cells.positions[i].y, cellSize / 2, BLACK);
			break;
		}
	}
}

void World::Update()
{
	Vector2 mousePos = GetMousePosition();
	int xIndex = int(mousePos.x / cellSize);
	int yIndex = int(mousePos.y / cellSize);
	int i = GetIndex(xIndex, yIndex, cells.WIDTH);

	// Set start
	if (IsMouseButtonReleased(0))
	{
		PlaceStart(i);
	}
	// Set goal
	else if (IsMouseButtonReleased(1))
	{
		PlaceGoal(i);
	}
	else if (IsMouseButtonReleased(2))
	{
		PlaceWall(i);
	}

	// Change display type
	if (IsKeyReleased(KEY_F1)) // None
	{
		displayType = DisplayType::None;
	}
	else if (IsKeyReleased(KEY_F2)) // Costs
	{
		displayType = DisplayType::Costs;
	}
	else if (IsKeyReleased(KEY_F3)) // Heuristics
	{
		displayType = DisplayType::Heuristics;
	}
}

Vector2 World::Get2DIndex(int i, int WIDTH)
{
	int x = i % WIDTH;
	int y = i / WIDTH;

	return Vector2(x, y);
}

void World::SetCosts()
{
	while (!indexesNeedingCost.empty())
	{
		int i = indexesNeedingCost.front(); // Get the front index
		indexesNeedingCost.pop(); // Remove from queue

		Vector2 index2D = Get2DIndex(i, cells.WIDTH);
		SetSurroundingCosts(index2D.x, index2D.y);
	}
}

void World::SetSurroundingCosts(int t_startingX, int t_startingY)
{
	int startingIndex = GetIndex(t_startingX, t_startingY, cells.WIDTH);
	int startingCost = cells.costs[startingIndex];

	for (int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for (int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if (yOffset == 0 && xOffset == 0) // Don't check itself
				continue;

			int x = t_startingX + xOffset;
			int y = t_startingY + yOffset;

			int neighbor = GetIndex(x, y, cells.WIDTH);

			cells.costs[neighbor] = startingCost + 1;

			// Add neighbor cells to a queue
			AddSurroundingToQueue(x, y);
		}
	}
}

void World::AddSurroundingToQueue(int t_startingX, int t_startingY)
{
	for (int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for (int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if (yOffset == 0 && xOffset == 0) // Don't check itself
				continue;

			int x = t_startingX + xOffset;
			int y = t_startingY + yOffset;
			int i = GetIndex(x, y, cells.WIDTH);


			// Don't add if it's a wall
			if (cells.costs[i] == DEFAULT_COST && cells.costs[i] != WALL_COST)
			{
				std::cout << "Cost (Pre-queue): " << cells.costs[i] << "\n";
				indexesNeedingCost.push(i);
			}
		}
	}
}

void World::SetHeuristics()
{
	for (int i = 0; i < amountOfCells; i++)
	{
		Vector2 goalPos = cells.positions[goalIndex];
		Vector2 currentPos = cells.positions[i];
		float dist = Vector2DistanceSqr(currentPos, goalPos);
		cells.heuristics[i] = dist;
	}
}

void World::ResetCosts()
{
	for (int i = 0; i < amountOfCells; i++)
	{
		if (cells.costs[i] != WALL_COST)
			cells.costs[i] = DEFAULT_COST;
	}
}

void World::PlaceStart(int i)
{
	if (i == goalIndex)// Dont replace end
		return;

	// ResetCosts();

	// Set old back to default
	cells.color[startIndex] = BASE_COLOR;
	cells.costs[startIndex] = DEFAULT_COST;

	// Set new start
	startIndex = i;
	cells.color[i] = START_COLOR;
	cells.costs[i] = 0;

	Vector2 index2D = Get2DIndex(i, cells.WIDTH);

	AddSurroundingToQueue(index2D.x, index2D.y);

	SetCosts();
}

void World::PlaceGoal(int i)
{
	if (i == startIndex) // Dont replace start
		return;

	// Set old back to normal
	cells.color[goalIndex] = BASE_COLOR;

	// Set new goal
	goalIndex = i;
	cells.color[i] = GOAL_COLOR;

	if (startIndex != -1)
		SetHeuristics();
}

void World::PlaceWall(int i)
{
	if (i == startIndex || i == goalIndex) // Dont replace start or goal
		return;

	ResetCosts();

	cells.costs[i] = WALL_COST;
	cells.color[i] = WALL_COLOR;

	SetCosts();
}
