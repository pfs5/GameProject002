#pragma once
#include "Ball.h"
#include <SFML/Graphics.hpp>

class Pad {
public:
	enum Side {
		Left, Right
	};
private:
	Side m_side;
	float m_acceleration;
	float m_speed;

	sf::RectangleShape m_shape;
public:
	Pad(const Side& _side);
	~Pad();

	void input();
	void update(float _dt);
	void draw();

	const float& getSpeed();

	void collideWithBall(Ball& _ball);

	void reset();
};

