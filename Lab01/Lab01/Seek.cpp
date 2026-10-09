#include "Seek.h"

Seek::Seek(sf::Vector2f& t_npcPos, sf::Vector2f& t_playerPos) : Behaviour(t_npcPos), playerPos(t_playerPos)
{
}

SteeringOutput Seek::Movement()
{
	SteeringOutput steeringOutput;

	steeringOutput.linear = SteeringTowardsTarget(playerPos);

	return steeringOutput;
}
