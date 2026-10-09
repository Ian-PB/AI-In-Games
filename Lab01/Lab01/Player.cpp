#include "Player.h"
#include "Globals.h"

Player::Player()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\ship.png"))
	{
		// Error
	}
	sprite.setTexture(texture, true);
	sprite.setOrigin({ 180, 180 });
	sprite.setScale({0.15f, 0.15f});
}

void Player::Init(sf::Vector2f startPos)
{
	sprite.setPosition(position);

	position = startPos;
	body.setPosition(position);
	body.setRadius(radius);
	body.setOrigin({ radius, radius });
	body.setFillColor(sf::Color::Blue);
}

void Player::Movement()
{
	sf::Vector2f direction = { 0.0f, 0.0f };

	// Up / Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		direction.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		direction.y = 1;
	}
	// Left / Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		direction.x = 1;
	}

	// Apply to velocity
	velocity.x += direction.x * speed;
	velocity.y += direction.y * speed;


	// Clamp speed
	if (velocity.length() > MAX_SPEED && velocity.length() > 0.0f)
	{
		velocity = velocity.normalized() * MAX_SPEED;
	}

	position += velocity;

	WorldLoop();

	body.setPosition(position);
	sprite.setPosition(position);

	RotateInMoveDir();

	// Drag
	velocity.x *= 0.97;
	velocity.y *= 0.97;
}

void Player::Render(sf::RenderWindow& m_window)
{
	m_window.draw(body);
	m_window.draw(sprite);
}

void Player::RotateInMoveDir()
{
	orientation = sf::radians(atan2(velocity.y, velocity.x)) + sf::degrees(90.0f);

	body.setRotation(orientation);
	sprite.setRotation(orientation);
}

void Player::WorldLoop()
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
