#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

#include "Behaviour.h"
#include "ObjectAvoidance.h"

enum BehaviourType {
	Arriving,
	Seeking,
	Wandering
};

class Npc
{
public:
	Npc();
	void Init(Player* p, sf::Vector2f startPos);

	bool isActive() { return active; }
	void Toggle() { active = !active; }

	void Movement(Npc t_objectPositions[], int AMOUNT_OF_OBJECTS);
	void Render(sf::RenderWindow& m_window);

	sf::Vector2f GetPos() { return position; }
	sf::Vector2f& GetPosRef() { return position; }

	sf::Vector2f GetVelocity() { return velocity; }
	sf::Vector2f& GetVelocityRef() { return velocity; }

	void SetupBehaviour(Behaviour* b);
	void SetupObjectAvoidance(ObjectAvoidance* t_avoidance);

	void SetColor(sf::Color c) { color = c; body.setFillColor(color); }
	void SetSpeed(float t_speed) { speed = t_speed; }

	bool IsPointInsideCone(sf::Vector2f t_point);
	void SetName(std::string t_name) { name.setString(t_name); }
	static sf::Texture texture;

private:

	bool active = true;

	sf::Font font;
	sf::Text name{ font };

	void RotateInMoveDir();
	void WorldLoop();

	sf::CircleShape body;

	// Behaviours
	Behaviour* behaviour;
	bool avoid = false;
	ObjectAvoidance* objectAvoidance;

	// Sprite
	sf::Sprite sprite{ texture };

	sf::Vector2f position;
	sf::Vector2f velocity = { 0.0f, 0.0f };
	float speed = 0.2f;
	const float MAX_SPEED = 5.0f;

	float radius = 20.0f;
	sf::Color color;

	sf::Angle orientation = sf::degrees(0.0f);

	// Vision cone
	void SetupVisionCone();
	void UpdateVisionCone();
	float coneThreshold = 35.0f;
	float coneRange = 150.0f;
	sf::RectangleShape coneLeft;
	sf::RectangleShape coneRight;
	int sizeOfNpcVector = 0;
	sf::Color coneColor;
	sf::Color seeingColor = sf::Color(255, 0, 0, 140);
	sf::Color notSeeingColor = sf::Color(0, 255, 0, 140);

	Player* player;
};