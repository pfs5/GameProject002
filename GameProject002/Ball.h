#pragma once
#include <SFML/Graphics.hpp>
class Ball {
	sf::CircleShape m_shape;

	sf::Vector2f m_speed;
public:
	Ball();
	~Ball();

	void input();
	void update(float _dt);
	void draw();

	void setPosition(const sf::Vector2f& _position);
	const sf::Vector2f& getPosition();
	const float& getRadius();
	
	const sf::Vector2f& getSpeed();
	void setSpeed(const sf::Vector2f& _speed);

	void reset();
};

