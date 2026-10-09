#pragma once
#include "Behaviour.h"
class Pursue :
    public Behaviour
{
public:
    Pursue(sf::Vector2f& t_npcPos, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVel);
    virtual SteeringOutput Movement();

private:
    const sf::Vector2f& playerPos;
    const sf::Vector2f& playerVelocity;
    const int PREDICTION_AMOUNT = 100;
};

