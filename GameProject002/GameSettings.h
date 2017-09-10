#pragma once

namespace GameSettings {
	const float PAD_SIZE = 150.f;
	const float PAD_WIDTH = 40.f;
	const float PAD_GAP = 20.f;

	const float PAD_ACCELERATION = 5000.f;
	const float PAD_MAX_SPEED = 100000.f;
	const float PAD_DRAG = .1f;

	const float BALL_RADIUS = 20.f;
	const float BALL_INIT_SPEED = 400.f;

	const float COLLISION_FACTOR = 0.4f;

	constexpr float SPEED_INCREASE_COEFF = 1.f + 1e-3;
}