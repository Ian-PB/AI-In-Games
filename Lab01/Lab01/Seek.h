#pragma once
#include "Behaviour.h"
class Seek : public Behaviour
{
public:
    Seek(sf::Vector2f& t_npcPos, sf::Vector2f& t_playerPos);
    virtual SteeringOutput Movement();

private:
    const sf::Vector2f& playerPos;
};

