#pragma once
#include "Behaviour.h"
class Arrive : public Behaviour
{
public:
    Arrive(sf::Vector2f& t_npcPos, sf::Vector2f& t_playerPos);
    virtual SteeringOutput Movement();

private:
    const sf::Vector2f& playerPos;
    float slowingDistance = 125.0f;
};

