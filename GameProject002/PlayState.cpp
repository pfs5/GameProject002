#include "stdafx.h"
#include "PlayState.h"
#include "Display.h"
#include "PointCounter.h"

PlayState::PlayState(Application& _app) : m_app(_app) {
	// Initialize pads
	m_pads.push_back(Pad(Pad::Left));
	m_pads.push_back(Pad(Pad::Right));
}


PlayState::~PlayState() {
}

void PlayState::input() {
	for (int i = 0; i < m_pads.size(); ++i) {
		m_pads[i].input();
	}

	m_ball.input();
}

void PlayState::update(float _dt) {
	for (int i = 0; i < m_pads.size(); ++i) {
		m_pads[i].update(_dt);
	}

	m_ball.update(_dt);

	collisionDetection();
}

void PlayState::draw() {
	for (int i = 0; i < m_pads.size(); ++i) {
		m_pads[i].draw();
	}

	m_ball.draw();

	PointCounter::getInstance().draw();
}

void PlayState::collisionDetection() {
	// Ball - Wall collision
	sf::Vector2f position (m_ball.getPosition());
	float radius = m_ball.getRadius();
	sf::Vector2u windowSize = Display::getWindow().getSize();
	sf::Vector2f speed(m_ball.getSpeed());
	
	// x axis
	if (position.x - radius < 0.f) {
		position.x = radius;
		speed.x = -speed.x;

		// Point
		if (PointCounter::getInstance().addPoint(1)) {
			m_app.popGameState();
		}

		reset();
		return;
	}
	else if (position.x + radius > windowSize.x) {
		position.x = windowSize.x - radius;
		speed.x = -speed.x;
	
		// Point
		if (PointCounter::getInstance().addPoint(0)) {
			m_app.popGameState();
		}

		reset();
		return;
	}

	// y axis
	if (position.y - radius < 0.f) {
		position.y = radius;
		speed.y = -speed.y;
	}
	else if (position.y + radius > windowSize.y) {
		position.y = windowSize.y - radius;
		speed.y = -speed.y;
	}

	m_ball.setPosition(position);
	m_ball.setSpeed(speed);

	// Ball - Pad collision
	for (int i = 0; i < m_pads.size(); ++i) {
		m_pads[i].collideWithBall(m_ball);
	}
	
}

void PlayState::reset() {
	for (int i = 0; i < m_pads.size(); ++i) {
		m_pads[i].reset();
	}
	m_ball.reset();
}
