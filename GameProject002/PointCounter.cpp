#include "stdafx.h"
#include "PointCounter.h"
#include "Display.h"
#include "Util.h"

PointCounter::PointCounter() : m_leftPoints(0), m_rightPoints(0) {
	if (!m_numbers.loadFromFile("numbers.png")) {
		Util::printMessage("[PointCounter] Error loading numbers.png");
	}

	m_leftScore.setTexture(m_numbers);
	m_rightScore.setTexture(m_numbers);

	m_leftScore.setTextureRect(sf::IntRect(0.f, 0.f, NUMBER_WIDTH, NUMBER_HEIGHT));
	m_rightScore.setTextureRect(sf::IntRect(0.f, 0.f, NUMBER_WIDTH, NUMBER_HEIGHT));

	m_leftScore.setPosition(Display::getWindow().getSize().x / 2.f - NUMBER_WIDTH * 3.f, NUMBER_HEIGHT / 2.f);
	m_rightScore.setPosition(Display::getWindow().getSize().x / 2.f + NUMBER_WIDTH * 2.f, NUMBER_HEIGHT / 2.f);
}


PointCounter::~PointCounter() {
}

void PointCounter::draw() {
	Display::draw(m_leftScore);
	Display::draw(m_rightScore);
}

bool PointCounter::addPoint(int _player) {
	if (_player == 0) {
		m_leftPoints++;
	}
	else if (_player == 1) {
		m_rightPoints++;
	}

	m_leftScore.setTextureRect(sf::IntRect(m_leftPoints * NUMBER_WIDTH, 0.f, NUMBER_WIDTH, NUMBER_HEIGHT));
	m_rightScore.setTextureRect(sf::IntRect(m_rightPoints * NUMBER_WIDTH, 0.f, NUMBER_WIDTH, NUMBER_HEIGHT));

	if (m_leftPoints >= 10 || m_rightPoints >= 10) {
		return true;
	}
	return false;
}

void PointCounter::initSprite(sf::Sprite & _sprite) {
	_sprite.setTexture(m_numbers);
	_sprite.setTextureRect(sf::IntRect(0.f, 0.f, NUMBER_WIDTH, NUMBER_HEIGHT));
}
