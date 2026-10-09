#pragma once
#include "Behaviour.h"

class Npc;

class ObjectAvoidance
{
public:
    ObjectAvoidance(sf::Vector2f& t_npcPos);
    SteeringOutput AvoidObjects(sf::Vector2f t_objectPositions[], int AMOUNT_OF_OBJECTS);

private:
    sf::Vector2f& npcPos;
    const float STRENGTH = 0.3f;
};

#include "Npc.h"