#pragma once
#include <raylib.h>
#include <queue>

struct Cells
{
	void GetCosts();
	void GetHeuristics();

	static const int WIDTH = 100;
	static const int HEIGHT = 100;

	Vector2 positions[WIDTH * HEIGHT]; // Top left corner
	Vector2 directions[WIDTH * HEIGHT];
	int costs[WIDTH * HEIGHT];
	float heuristics[WIDTH * HEIGHT];

	Color color[WIDTH * HEIGHT];
};

enum class DisplayType
{
	None,
	Costs,
	Heuristics,
};

class World
{
public:
	void Setup();
	void Draw();
	void Update();

private:
	static int GetIndex(int x, int y, int WIDTH) { return (y * WIDTH + x); }
	static Vector2 Get2DIndex(int i, int WIDTH);

	void SetCosts();
	void SetSurroundingCosts(int t_startingX, int t_startingY);
	void AddSurroundingToQueue(int t_startingX, int t_startingY);
	void SetHeuristics();

	void ResetCosts();

	void PlaceStart(int i);
	void PlaceGoal(int i);
	void PlaceWall(int i);

	float cellSize = 0;

	int amountOfCells = 0;
	Cells cells;

	DisplayType displayType = DisplayType::None;

	int startIndex = -1;
	int goalIndex = -1;

	std::queue<int> indexesNeedingCost;

	const int DEFAULT_COST = -1;
	const int WALL_COST = 999999;
	const Color BASE_COLOR = BLUE;
	const Color GOAL_COLOR = RED;
	const Color START_COLOR = GREEN;
	const Color WALL_COLOR = BLACK;
};
