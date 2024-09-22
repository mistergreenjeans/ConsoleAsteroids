#include "Bullet.h"

Bullet::Bullet(Vec2 pos1, Vec2 vel1) :Entity(pos1, vel1, atan2(vel1.y, vel1.x), 2) {
	model.push_back(Vec2(3, 0));
	model.push_back(Vec2(0, 1));
	model.push_back(Vec2(0, -1));
	timeLeft = .75;
}

void Bullet::update(ConsoleGraphicsEngine temp, float fElapsedTime) {
	pos += vel * fElapsedTime;
	angle = atan2(vel.y, vel.x);
	if (pos.x > temp.width - 1) {
		pos.x -= temp.width;
	}
	if (pos.x < 0) {
		pos.x += temp.width;
	}
	if (pos.y > temp.height - 1) {
		pos.y -= temp.height;
	}
	if (pos.y < 0) {
		pos.y += temp.height;
	}
	timeLeft -= fElapsedTime;
}