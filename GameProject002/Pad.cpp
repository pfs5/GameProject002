#include "stdafx.h"
#include "Pad.h"
#include "Display.h"
#include "GameSettings.h"
#include <iostream>

Pad::Pad(const Side& _side) : m_side(_side), m_acceleration(0.f), m_speed(0.f) {
	// Init shape
	m_shape.setSize(sf::Vector2f(GameSettings::PAD_WIDTH, GameSettings::PAD_SIZE));
	sf::Vector2f position(GameSettings::PAD_GAP, Display::getWindow().getSize().y / 2.f);
	if (_side == Right) {
		position.x = Display::getWindow().getSize().x - GameSettings::PAD_WIDTH - GameSettings::PAD_GAP;
	}
	m_shape.setPosition(position);
	m_shape.setOrigin(0.f, GameSettings::PAD_SIZE / 2.f);

	m_shape.setFillColor(sf::Color::White);
}


Pad::~Pad() {
}

void Pad::input() {
	sf::Keyboard::Key upControll;
	sf::Keyboard::Key downControll;

	switch (m_side) {
	case Left:
		upControll = sf::Keyboard::W;
		downControll = sf::Keyboard::S;
		break;
	case Right:
		upControll = sf::Keyboard::Up;
		downControll = sf::Keyboard::Down;
		break;
	}

	if (sf::Keyboard::isKeyPressed(upControll)) {
		m_acceleration = -GameSettings::PAD_ACCELERATION;
	}
	else if (sf::Keyboard::isKeyPressed(downControll)) {
		m_acceleration = GameSettings::PAD_ACCELERATION;
	}
	else {
		m_acceleration = 0.f;
	}
}

void Pad::update(float _dt) {
	float newPosition = m_shape.getPosition().y + m_speed * _dt;
	if (newPosition >= 0.f && newPosition <= Display::getWindow().getSize().y) {
		m_shape.move(sf::Vector2f(0.f, m_speed * _dt));
	} else {
		m_speed = 0.f;
	}

	m_speed *= (1.f - GameSettings::PAD_DRAG);
	if (fabsf(m_speed + m_acceleration * _dt) <= GameSettings::PAD_MAX_SPEED) {
		m_speed += m_acceleration * _dt;
	}
}

void Pad::draw() {
	Display::draw(m_shape);
}

const float & Pad::getSpeed() {
	return m_speed;
}

void Pad::collideWithBall(Ball& _ball) {
	sf::Vector2f ballPosition = _ball.getPosition();
	sf::Vector2f padPosition = m_shape.getPosition();
	float ballRadius = _ball.getRadius();
	float padSizeHalf = m_shape.getSize().y / 2.f;
	float padWidth = m_shape.getSize().x;

	// y axis
	float diff1 = ballPosition.y + ballRadius - (padPosition.y - padSizeHalf);
	float diff2 = padPosition.y + padSizeHalf - (ballPosition.y - ballRadius);

	if (diff1 > 0.f && diff2 > 0.f) {
		float yCollisionDepth = fminf(diff1, diff2);
		if (diff1 < diff2) {
			yCollisionDepth *= -1.f;
		}

		float xCollisionDepth = (m_side == Left) ? (padPosition.x + padWidth - (ballPosition.x - ballRadius)) : (ballPosition.x + ballRadius - padPosition.x);
		
		if (xCollisionDepth > 0) {
			if (m_side == Right) {
				xCollisionDepth *= -1.f;
			}

			sf::Vector2f newBallPosition(_ball.getPosition());
			sf::Vector2f newBallSpeed(_ball.getSpeed());

			if (fabsf(yCollisionDepth) < xCollisionDepth) {
				newBallPosition += sf::Vector2f(0.f, yCollisionDepth);
				newBallSpeed.y = - newBallSpeed.y + GameSettings::COLLISION_FACTOR * m_speed;
			}
			else {
				newBallPosition += sf::Vector2f(xCollisionDepth, 0.f);
				newBallSpeed.x *= -1.f;
				newBallSpeed.y += GameSettings::COLLISION_FACTOR * m_speed;
			}

			_ball.setPosition(newBallPosition);
			_ball.setSpeed(newBallSpeed);
		}
	}
}

void Pad::reset() {
	sf::Vector2f position(GameSettings::PAD_GAP, Display::getWindow().getSize().y / 2.f - GameSettings::PAD_SIZE / 2.f);
	if (m_side == Right) {
		position.x = Display::getWindow().getSize().x - GameSettings::PAD_WIDTH - GameSettings::PAD_GAP;
	}
	m_shape.setPosition(position);

	m_speed = 0.f;
	m_acceleration = 0.f;
}
