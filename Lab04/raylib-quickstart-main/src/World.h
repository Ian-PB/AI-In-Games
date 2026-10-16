#pragma once
#include <raylib.h>

struct Cells
{
	void GetCosts();
	void GetHeuristics();

	static const int WIDTH = 100;
	static const int HEIGHT = 100;

	Vector2 positions[WIDTH * HEIGHT]; // Top left corner
	Vector2 directions[WIDTH * HEIGHT];
	int cost[WIDTH * HEIGHT];
	float heuristics[WIDTH * HEIGHT];
};

class World
{
public:
	void Setup();
	void Draw();
	void Update();

private:
	int GetWidth() { return cells.WIDTH; }
	static int GetIndex(int x, int y, int WIDTH) { return (y * WIDTH + x); }

	float cellSize = 0;

	int amountOfCells = 0;
	Cells cells;

	int startIndex = -1;
	int goalIndex = -1;
};
