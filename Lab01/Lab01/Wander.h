#pragma once
#include "Behaviour.h"
class Wander : public Behaviour
{
public:
	Wander(sf::Vector2f& t_npcPos);
	virtual SteeringOutput Movement();

private:
	void SetRandWanderPos();

	bool targetSet = false;
	sf::Vector2f wanderTarget;
	const int MIN_WANDER_DIST = 5;
	const int MAX_WANDER_DIST = 100;
};

