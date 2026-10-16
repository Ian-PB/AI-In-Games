#pragma once
#include "Behaviour.h"

class Npc;

class Swarming : public Behaviour
{
public:
	Swarming(sf::Vector2f& t_npcPos, sf::Vector2f& t_npcVelocity, Npc t_allNpcs[], int t_ALL_NPCS_SIZE);
	~Swarming();

	virtual SteeringOutput Movement();
	void Render(sf::RenderWindow& m_window) override;

private:

	struct NpcInfo
	{
		sf::Vector2f position;
		sf::Vector2f velocity;
	};

	void SetNpcsInRange();

	const int ALL_NPCS_SIZE;
	Npc* allNpcs;
	int amountOfNpcsInRange = 0;
	NpcInfo* npcsInfoInRange;

	// Detection
	sf::CircleShape detectionVisual;
	float detectionRadius = 350.0f;

	// Lennard-Jones constants
	const float A = 1500000.0f;
	const float B = 500.0f;
	const float N = 4.0f;
	const float M = 2.0f;

	sf::Vector2f& npcVelocity;
};

#include "Npc.h"