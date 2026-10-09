#include "Flocking.h"
#include <iostream>

Flocking::Flocking(sf::Vector2f& t_npcPos, sf::Vector2f& t_npcVelocity, Npc t_allNpcs[], int t_ALL_NPCS_SIZE) : Behaviour(t_npcPos), npcVelocity(t_npcVelocity), allNpcs(t_allNpcs), ALL_NPCS_SIZE(t_ALL_NPCS_SIZE)
{
    npcsInfoInRange = new NpcInfo[ALL_NPCS_SIZE];

    detectionVisual.setFillColor({ 255, 255, 255, 2 });
    detectionVisual.setRadius(detectionRadius);
    detectionVisual.setOrigin({ detectionRadius, detectionRadius });

    seperationVisual.setFillColor({ 255, 0, 0, 2 });
    seperationVisual.setRadius(seperationRadius);
    seperationVisual.setOrigin({ seperationRadius, seperationRadius });
}
Flocking::~Flocking()
{
    delete[] npcsInfoInRange;
}

SteeringOutput Flocking::Movement()
{
    SteeringOutput steeringOutput;

    detectionVisual.setPosition(npcPos);
    seperationVisual.setPosition(npcPos);

    // Update npcs in range
    SetNpcsInRange();

    if (amountOfNpcsInRange <= 0)
    {
        return steeringOutput;
    }

    // Cohesion - Steer towards average position of near npcs
    sf::Vector2f cohesion = { 0.0f, 0.0f };

    sf::Vector2f averagePos = GetAveragePosOfNeighbours();
    sf::Vector2f dirToAverage = averagePos - npcPos;
    if (dirToAverage.length() > 0.0f)
    {
        cohesion = dirToAverage.normalized() * cohesionStrength;
    }

    // Alignment - Steer to align with average velocity of near npcs
    sf::Vector2f alignment = { 0.0f, 0.0f };
    alignment = GetAverageVelocityOfNeighbours();

    if (alignment.length() > 0.0f)
    {
        alignment = alignment.normalized();
        alignment *= alignmentStrength;
    }

    // Seperation - Steer away from near npcs
    sf::Vector2f seperation = GetSeperationFromNeighbours();
    if (seperation.length() > 0)
    {
        seperation = seperation.normalized();
        seperation *= seperationStrength;
    }

    steeringOutput.linear = cohesion + alignment + (seperation);

    return steeringOutput;
}

void Flocking::Render(sf::RenderWindow& m_window)
{
    m_window.draw(detectionVisual);
    m_window.draw(seperationVisual);
}

sf::Vector2f Flocking::GetAveragePosOfNeighbours()
{
    sf::Vector2f totalPos = {0.0f, 0.0f};

    if (amountOfNpcsInRange <= 0)
        return npcPos;

    for (int i = 0; i < amountOfNpcsInRange; i++)
    {
        totalPos += npcsInfoInRange[i].position;
    }

    sf::Vector2f averagePos = (totalPos / (float)amountOfNpcsInRange);

    return averagePos;
}

sf::Vector2f Flocking::GetAverageVelocityOfNeighbours()
{
    sf::Vector2f totalVelocity = { 0.0f, 0.0f };
    for (int i = 0; i < amountOfNpcsInRange; i++)
    {
        totalVelocity += npcsInfoInRange[i].velocity;
    }

    sf::Vector2f averageVelocity = (totalVelocity / (float)amountOfNpcsInRange);

    return averageVelocity;
}

sf::Vector2f Flocking::GetSeperationFromNeighbours()
{
    sf::Vector2f totalSeperation = { 0.0f, 0.0f };

    for (int i = 0; i < amountOfNpcsInRange; i++)
    {
        sf::Vector2f dirAway = npcPos - npcsInfoInRange[i].position;

        float distance = dirAway.length();

        if (distance > 0.0f && distance < seperationRadius)
        {
            totalSeperation += dirAway.normalized() / distance;
        }
    }

    return totalSeperation;
}

void Flocking::SetNpcsInRange()
{
    amountOfNpcsInRange = 0;

    for (int i = 0; i < ALL_NPCS_SIZE; i++)
    {
        sf::Vector2f dirToNpc = npcPos - allNpcs[i].GetPos();

        // Skip self
        if (&allNpcs[i].GetPosRef() == &npcPos)
        {
            continue;
        }
        // Skip inactive npcs
        if (!allNpcs[i].isActive())
        {
            continue;
        }

        // Skip if not in range
        if (dirToNpc.length() > detectionRadius)
        {
            continue;
        }

        // Was in range so add to array
        npcsInfoInRange[amountOfNpcsInRange].position = allNpcs[i].GetPos();
        npcsInfoInRange[amountOfNpcsInRange].velocity = allNpcs[i].GetVelocity();
        amountOfNpcsInRange++;
    }
}
