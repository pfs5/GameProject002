#include "stdafx.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Display.h"
#include <iostream>

Ball::Ball() : m_speed(GameSettings::BALL_INIT_SPEED, 0.f){
	// Init ball
	m_shape.setRadius(GameSettings::BALL_RADIUS);
	m_shape.setOrigin(GameSettings::BALL_RADIUS, GameSettings::BALL_RADIUS);
	m_shape.setPosition(Display::getWindow().getSize().x / 2.f, Display::getWindow().getSize().y / 2.f);

	m_shape.setFillColor(sf::Color::White);
}


Ball::~Ball() {
}

void Ball::input() {
}

void Ball::update(float _dt) {
	m_shape.move(m_speed * _dt);

	m_speed *= GameSettings::SPEED_INCREASE_COEFF;
}

void Ball::draw() {
	Display::draw(m_shape);
}

void Ball::setPosition(const sf::Vector2f & _position) {
	m_shape.setPosition(_position);
}

const sf::Vector2f & Ball::getPosition() {
	return m_shape.getPosition();
}

const float & Ball::getRadius() {
	return m_shape.getRadius();
}

const sf::Vector2f & Ball::getSpeed() {
	return m_speed;
}

void Ball::setSpeed(const sf::Vector2f & _speed) {
	m_speed = _speed;
}

void Ball::reset() {
	m_shape.setPosition(Display::getWindow().getSize().x / 2.f, Display::getWindow().getSize().y / 2.f);
	m_speed = sf::Vector2f(GameSettings::BALL_INIT_SPEED, 0.f);
}
