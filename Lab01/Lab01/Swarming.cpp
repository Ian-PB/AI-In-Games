#include "Swarming.h"
#include <iostream>

Swarming::Swarming(sf::Vector2f& t_npcPos, sf::Vector2f& t_npcVelocity, Npc t_allNpcs[], int t_ALL_NPCS_SIZE) : Behaviour(t_npcPos), npcVelocity(t_npcVelocity), allNpcs(t_allNpcs), ALL_NPCS_SIZE(t_ALL_NPCS_SIZE)
{
    npcsInfoInRange = new NpcInfo[ALL_NPCS_SIZE];

    detectionVisual.setFillColor({ 255, 255, 255, 2 });
    detectionVisual.setRadius(detectionRadius);
    detectionVisual.setOrigin({ detectionRadius, detectionRadius });
}
Swarming::~Swarming()
{
    delete[] npcsInfoInRange;
}

SteeringOutput Swarming::Movement()
{
    SteeringOutput steeringOutput;

    detectionVisual.setPosition(npcPos);

    SetNpcsInRange();

    sf::Vector2f totalForce = { 0.0f, 0.0f };

    for (int i = 0; i < amountOfNpcsInRange; i++)
    {
        sf::Vector2f dirToNpc = npcsInfoInRange[i].position - npcPos;

        float distance = dirToNpc.length();

        // No dividing by zero
        if (distance <= 0.0f)
            continue;

        sf::Vector2f direction = dirToNpc.normalized();

        // Lennard-Jones force equation
        float force = -A / pow(distance, N) + B / pow(distance, M);

        totalForce += direction * force;
    }

    steeringOutput.linear = totalForce;

    steeringOutput.realVelocity = true;
    return steeringOutput;
}

void Swarming::Render(sf::RenderWindow& m_window)
{
    m_window.draw(detectionVisual);
}

void Swarming::SetNpcsInRange()
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
