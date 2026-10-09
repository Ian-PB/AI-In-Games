#include "Pursue.h"

Pursue::Pursue(sf::Vector2f& t_npcPos, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVel) : Behaviour(t_npcPos), playerPos(t_playerPos), playerVelocity(t_playerVel)
{
}

SteeringOutput Pursue::Movement()
{
	SteeringOutput steeringOutput;

	sf::Vector2f scaledVelocity = playerVelocity;
	scaledVelocity.x *= PREDICTION_AMOUNT;
	scaledVelocity.y *= PREDICTION_AMOUNT;

	sf::Vector2f predictedPos = playerPos + scaledVelocity;

	steeringOutput.linear = SteeringTowardsTarget(predictedPos);

	return steeringOutput;
}
