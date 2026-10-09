#pragma once
#include <SFML/Graphics.hpp>

struct SteeringOutput
{
	bool realVelocity = false;

	sf::Vector2f linear = { 0.0f, 0.0f };
	sf::Vector2f angular = { 0.0f, 0.0f };
};

class Behaviour
{
public:
	Behaviour(sf::Vector2f& t_npcPos);
	virtual SteeringOutput Movement() = 0;
	virtual void Render(sf::RenderWindow& m_window);


protected:
	sf::Vector2f SteeringTowardsTarget(sf::Vector2f t_target);

	const sf::Vector2f& npcPos;
};