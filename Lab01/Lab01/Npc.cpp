#include "Npc.h"
#include "Globals.h"
#include <iostream>

sf::Texture Npc::texture;

Npc::Npc()
{
	if (!font.openFromFile(("ASSETS\\FONTS\\Jersey20-Regular.ttf")))
	{
		std::cout << "Font not found\n";
	}
	name.setFont(font);
	name.setFillColor(sf::Color::Black);
	name.setCharacterSize(24);
	name.setString("TEMP");

	orientation = sf::degrees(rand() % 360);

	srand(time(nullptr));

	SetupVisionCone();
}

void Npc::SetupBehaviour(Behaviour* b)
{
	behaviour = b;
}

void Npc::SetupObjectAvoidance(ObjectAvoidance* t_avoidance)
{
	objectAvoidance = t_avoidance;
}

void Npc::Init(Player* p, sf::Vector2f startPos)
{
	player = p;
	position = startPos;
	sprite.setPosition(position);
	body.setPosition(position);
	body.setRadius(radius);
	body.setOrigin({ radius, radius});

	sprite.setTexture(texture, true);
	sprite.setOrigin({ 2000, 1500 });
	sprite.setScale({ 0.015f, 0.015f });

	active = true;
}

void Npc::Movement(Npc t_objects[], int t_AMOUNT_OF_OBJECTS)
{
	if (!active)
		return;
	if (behaviour == nullptr)
		return;

	// Apply steerings to one variable
	sf::Vector2f totalSteering = { 0.0f, 0.0f };

	SteeringOutput behaviourSteering = behaviour->Movement();
	totalSteering += behaviourSteering.linear;

	// Used for swarming
	if (behaviourSteering.realVelocity)
	{
		velocity += totalSteering;
	}
	else
	{
		// Normalize and * by speed after all steering is added
		if (totalSteering.length() > 0.0f)
			totalSteering = totalSteering.normalized();

		velocity += totalSteering * speed;
	}

	if (avoid)
	{
		// Get the npcs in the cone
		sf::Vector2f* objectsInSight = new sf::Vector2f[t_AMOUNT_OF_OBJECTS];
		sizeOfNpcVector = 0;
		for (int i = 0; i < t_AMOUNT_OF_OBJECTS; i++)
		{
			if (!t_objects[i].isActive())
				continue;

			if (IsPointInsideCone(t_objects[i].GetPos()))
			{
				objectsInSight[sizeOfNpcVector] = t_objects[i].GetPos();
				sizeOfNpcVector++;
			}
		}
		// Make sure there are npcs seen by cone
		if (sizeOfNpcVector > 0)
		{
			coneColor = seeingColor;
			velocity += objectAvoidance->AvoidObjects(objectsInSight, sizeOfNpcVector).linear;
		}
		else
		{
			coneColor = notSeeingColor;
		}
		coneLeft.setFillColor(coneColor);
		coneRight.setFillColor(coneColor);
	}

	// Clamp speed
	if (velocity.length() > MAX_SPEED)
	{
		velocity = velocity.normalized() * MAX_SPEED;
	}

	position += velocity;

	WorldLoop();

	name.setPosition({ position.x, position.y + 20 });
	body.setPosition(position);
	sprite.setPosition(position);

	RotateInMoveDir();

	// Drag
	velocity.x *= 0.97f;
	velocity.y *= 0.97f;
}

void Npc::Render(sf::RenderWindow& m_window)
{
	if (!active)
		return;

	m_window.draw(body);
	m_window.draw(sprite);

	behaviour->Render(m_window);

	// Vision cone
	if (avoid)
	{
		m_window.draw(coneLeft);
		m_window.draw(coneRight);
	}

	if (name.getString() != "")
		m_window.draw(name);
}


bool Npc::IsPointInsideCone(sf::Vector2f t_point)
{
	// This techically doesnt detect obstacles "properly" but it seems to allow for better avoidant behaviour than the "working" version
	bool isPointInRange = false;
	bool isPointWithinCone = false;

	// Check the distance to the point from the npc
	sf::Vector2f dirToTarget = t_point - position;

	if (dirToTarget.length() <= coneRange)
	{
		isPointInRange = true;
	}

	float orientationAsRadians = orientation.asRadians();
	sf::Vector2f coneForward = { cosf(orientationAsRadians), sinf(orientationAsRadians) };
	float dotProduct = dirToTarget.dot(coneForward);
	
	// Converted to radians
	float threshold = cosf(coneThreshold * (3.14f / 180.0f));

	isPointWithinCone = dotProduct >= threshold;

	bool canSeePoint = isPointInRange && isPointWithinCone;
	return canSeePoint;
}

void Npc::SetupVisionCone()
{
	coneColor = notSeeingColor;
	coneLeft.setSize({ 6, coneRange });
	coneLeft.setOrigin({ 3, coneRange });
	coneLeft.setFillColor(coneColor);

	coneRight.setSize({ 6, coneRange });
	coneRight.setOrigin({ 3, coneRange });
	coneRight.setFillColor(coneColor);
}

void Npc::UpdateVisionCone()
{
	coneLeft.setPosition(position);
	coneLeft.setRotation(orientation + sf::degrees(-coneThreshold));

	coneRight.setPosition(position);
	coneRight.setRotation(orientation + sf::degrees(coneThreshold));
}

void Npc::RotateInMoveDir()
{
	orientation = sf::radians(atan2(velocity.y, velocity.x)) + sf::degrees(90.0f);

	body.setRotation(orientation);
	sprite.setRotation(orientation);

	UpdateVisionCone();
}

void Npc::WorldLoop()
{
	// Check if should loop around screen
	if (position.x > windowSize.x + radius)
	{
		position.x = -radius;
	}
	else if (position.x < -radius)
	{
		position.x = windowSize.x + radius;
	}

	if (position.y > windowSize.y + radius)
	{
		position.y = -radius;
	}
	else if (position.y < -radius)
	{
		position.y = windowSize.y + radius;
	}
}
