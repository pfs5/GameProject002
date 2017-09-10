#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class PointCounter {
	sf::Texture m_numbers;
	sf::Sprite m_leftScore;
	sf::Sprite m_rightScore;

	int m_leftPoints;
	int m_rightPoints;

	const float NUMBER_WIDTH = 80.f;
	const float NUMBER_HEIGHT = 100.f;
public:
	~PointCounter();

	PointCounter(const PointCounter&) = delete;
	PointCounter& operator=(const PointCounter&) = delete;

	static PointCounter& getInstance() {
		static PointCounter instance;
		return instance;
	}

	void draw();

	bool addPoint(int _player);
private:
	PointCounter();
	void initSprite(sf::Sprite& _sprite);
};

