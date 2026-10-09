#include "Wander.h"

Wander::Wander(sf::Vector2f& t_npcPos) : Behaviour(t_npcPos)
{
}

SteeringOutput Wander::Movement()
{
	if (!targetSet)
	{
		targetSet = true;
		SetRandWanderPos();
	}

	SteeringOutput steeringOutput;

	sf::Vector2f dirToTarget = npcPos - wanderTarget;
	float distToTarget = dirToTarget.length();
	if (distToTarget <= 15.0f)
	{
		SetRandWanderPos();
	}

	steeringOutput.linear = SteeringTowardsTarget(wanderTarget);


	return steeringOutput;
}

void Wander::SetRandWanderPos()
{
	// Generate random direction
	float x = (float)rand() / RAND_MAX * 2.0f - 1.0f;
	float y = (float)rand() / RAND_MAX * 2.0f - 1.0f;
	sf::Vector2f dir = { x, y };

	// Distance of wander
	float randWanderDist = (rand() % (MAX_WANDER_DIST - MIN_WANDER_DIST)) + MIN_WANDER_DIST;

	// Scale direction to wanderDistance
	dir *= randWanderDist;

	// Apply to the player's position
	sf::Vector2f result = npcPos + dir;

	wanderTarget = result;
}
