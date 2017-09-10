#include "stdafx.h"
#include "DefaultState.h"
#include "PlayState.h"
#include "Display.h"

DefaultState::DefaultState(Application& _app) : m_app(_app) {
	// Load logo
	m_logoTexture.loadFromFile("logo.png");
	m_logoSprite.setTexture(m_logoTexture);

	m_logoSprite.setOrigin(m_logoTexture.getSize().x / 2.f, m_logoTexture.getSize().y / 2.f);
	m_logoSprite.setPosition(sf::Vector2f(Display::getWindow().getSize().x / 2.f, Display::getWindow().getSize().y / 2.f));
}


DefaultState::~DefaultState() {
}

void DefaultState::input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		m_app.addGameState(new PlayState(m_app));
	}
}

void DefaultState::update(float _dt) {

}

void DefaultState::draw() {
	Display::draw(m_logoSprite);
}