#include "Behaviour.h"

Behaviour::Behaviour(sf::Vector2f& t_npcPos) : npcPos(t_npcPos)
{
}

void Behaviour::Render(sf::RenderWindow& m_window)
{
}

sf::Vector2f Behaviour::SteeringTowardsTarget(sf::Vector2f t_target)
{
	sf::Vector2f steering = t_target - npcPos;

	return steering;
}
