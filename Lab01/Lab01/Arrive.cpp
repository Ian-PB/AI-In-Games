#include "Arrive.h"

Arrive::Arrive(sf::Vector2f& t_npcPos, sf::Vector2f& t_playerPos) : Behaviour(t_npcPos), playerPos(t_playerPos)
{
}

SteeringOutput Arrive::Movement()
{
	SteeringOutput steeringOutput;
	sf::Vector2f dirToPlayer = npcPos - playerPos;
	float distToPlayer = dirToPlayer.length();

	// Default steering towards target
	steeringOutput.linear = SteeringTowardsTarget(playerPos);

	if (distToPlayer < slowingDistance)
	{
		// Stop / allow to drift to player
		steeringOutput.linear = { 0.0f, 0.0f };
	}

	return steeringOutput;
}
