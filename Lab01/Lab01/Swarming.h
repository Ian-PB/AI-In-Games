#pragma once
#include "Behaviour.h"

class Npc;

class Swarming : public Behaviour
{
public:
	Swarming(sf::Vector2f& t_npcPos, sf::Vector2f& t_npcVelocity, Npc t_allNpcs[], int t_ALL_NPCS_SIZE);
	virtual SteeringOutput Movement();
	void Render(sf::RenderWindow& m_window) override;

private:

	struct NpcInfo
	{
		sf::Vector2f position;
		sf::Vector2f velocity;
	};

	sf::Vector2f GetAveragePosOfNeighbours();
	sf::Vector2f GetAverageVelocityOfNeighbours();
	sf::Vector2f GetSeperationFromNeighbours();
	void SetNpcsInRange();

	const int ALL_NPCS_SIZE;
	Npc* allNpcs;
	int amountOfNpcsInRange = 0;
	NpcInfo* npcsInfoInRange;

	// Detection
	sf::CircleShape detectionVisual;
	float detectionRadius = 500.0f;
	sf::CircleShape seperationVisual;
	float seperationRadius = 50.0f;

	float cohesionStrength = 20.0f;
	float alignmentStrength = 20.0f;
	float seperationStrength = 0.1f;

	sf::Vector2f& npcVelocity;
};

#include "Npc.h"