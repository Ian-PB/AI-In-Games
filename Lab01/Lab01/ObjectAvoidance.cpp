#include "ObjectAvoidance.h"

ObjectAvoidance::ObjectAvoidance(sf::Vector2f& t_npcPos) : npcPos(t_npcPos)
{
}

SteeringOutput ObjectAvoidance::AvoidObjects(sf::Vector2f t_objectPositions[], int AMOUNT_OF_OBJECTS)
{
    SteeringOutput steeringOutput;
    sf::Vector2f avoidance = { 0.0f, 0.0f };

    for (int i = 0; i < AMOUNT_OF_OBJECTS; i++)
    {
        // Dont check against itself
        if (npcPos == t_objectPositions[i])
            continue;

        sf::Vector2f dirToObj = npcPos - t_objectPositions[i];
        sf::Vector2f dirAwayFromObj = dirToObj.rotatedBy(sf::degrees(60.0f));

        avoidance += dirAwayFromObj;
    }

    sf::Vector2f strengthenedAvoidance = avoidance.normalized();
    strengthenedAvoidance.x *= STRENGTH;
    strengthenedAvoidance.y *= STRENGTH;

    steeringOutput.linear = strengthenedAvoidance;

    return steeringOutput;
}
