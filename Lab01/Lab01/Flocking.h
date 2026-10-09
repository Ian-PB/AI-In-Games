#pragma once
#include "Behaviour.h"

class Npc;

class Flocking : public Behaviour
{
public:
	Flocking(sf::Vector2f& t_npcPos, sf::Vector2f& t_npcVelocity, Npc t_allNpcs[], int t_ALL_NPCS_SIZE);
	~Flocking();

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
	float detectionRadius = 150.0f;
	sf::CircleShape seperationVisual;
	float seperationRadius = 120.0f;

	float cohesionStrength = 1.0f;
	float alignmentStrength = 1.0f;
	float seperationStrength = 1.2f;

	sf::Vector2f& npcVelocity;
};

#include "Npc.h"