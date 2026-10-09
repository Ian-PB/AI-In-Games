#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void Init(sf::Vector2f startPos);

	void Movement();
	void Render(sf::RenderWindow& m_window);

	sf::Vector2f GetPos() { return position; }
	sf::Vector2f& GetPosRef() { return position; }
	sf::Vector2f GetVel() { return velocity; }
	sf::Vector2f& GetVelRef() { return velocity; }

private:
	void RotateInMoveDir();
	void WorldLoop();

	sf::CircleShape body;

	// Sprite
	sf::Texture texture;
	sf::Sprite sprite{ texture };

	sf::Vector2f position;
	sf::Vector2f velocity = { 0.0f, 0.0f };
	float speed = 0.2;
	const float MAX_SPEED = 50.0f;

	float radius = 20;

	sf::Angle orientation = sf::degrees(0.0f);
};

