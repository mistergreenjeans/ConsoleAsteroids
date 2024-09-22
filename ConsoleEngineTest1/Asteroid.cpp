#include "Asteroid.h"



Asteroid::Asteroid(Vec2 pos1, Vec2 vel1, double r, double sMax, int res1) :Entity(pos1, vel1, toRadians(0), r) {
	splitMax = sMax;
	splits = 0;
	res = res1;
	rotationalVel = toRadians(((float)rand() / (float)RAND_MAX) * 90 - 90 / 2);
	for (int i = 0; i < res; i++) {
		model.push_back(Vec2((radius + ((float)rand() / (float)RAND_MAX) * r / 2 - 4 / 4) * cos(toRadians((360 / (double)res) * i)), (radius + ((float)rand() / (float)RAND_MAX) * r / 2 - r / 4) * sin(toRadians((360 / (double)res) * i))));
	}
}

Asteroid::Asteroid(Vec2 pos1, Vec2 vel1, double r, double sMax, double splitNum, int res1) :Entity(pos1, vel1, toRadians(0), r) {
	splitMax = sMax;
	splits = splitNum;
	if (splits == 0) {
		life = 0;
	}
	else {
		life = 100;
	}
	res = res1;
	rotationalVel = toRadians(((float)rand() / (float)RAND_MAX) * 90 - 90 / 2);
	for (int i = 0; i < res; i++) {
		model.push_back(Vec2((radius + ((float)rand() / (float)RAND_MAX) * r / 2 - 4 / 4) * cos(toRadians((360 / (double)res) * i)), (radius + ((float)rand() / (float)RAND_MAX) * r / 2 - r / 4) * sin(toRadians((360 / (double)res) * i))));
	}
}
vector<Asteroid> Asteroid::split() {
	vector<Asteroid> temp;
	splits++;
	if (splits <= splitMax) {
		Vec2 newVel = Vec2((double)((float)rand() / (float)RAND_MAX) * 40, (double)((float)rand() / (float)RAND_MAX) * 40);
		temp.push_back(Asteroid(pos, vel + newVel, radius / 2, splitMax, splits, res));

		temp.push_back(Asteroid(pos, vel - newVel, radius / 2, splitMax, splits, res));
	}
	return temp;
}

void Asteroid::updatePos(ConsoleGraphicsEngine temp, float fElapsedTime) {
	pos += vel * fElapsedTime;
	angle += rotationalVel * fElapsedTime;
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
	if (vel.getMagnitude() > 100) {
		color = COLOR(FG_DARK_YELLOW) + COLOR(BG_DARK_YELLOW);
	}
}