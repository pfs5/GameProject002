#pragma once
#include "GameState.h"
#include "Application.h"
#include "Pad.h"
#include "Ball.h"
class PlayState : public GameState {
	Application& m_app;

	std::vector<Pad> m_pads;
	Ball m_ball;


public:
	PlayState(Application& _app);
	~PlayState();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;

private:
	void collisionDetection();
	void reset();
};

