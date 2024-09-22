#include "Player.h"

Player::Player(const ConsoleGraphicsEngine& temp) :Entity(Vec2(temp.width / 2, temp.height / 2), Vec2(0, 0), 0, 4) {
	model.push_back(Vec2(10, 0));
	model.push_back(Vec2(0, 4));
	model.push_back(Vec2(2, 0));
	model.push_back(Vec2(0, -4));
	lives = 3;
	isOnScreen = true;
	thrustOn = false;
	helper = 0;

}

void Player::thrust(const double power, const float fElapsedTime, 
					const bool on, const bool left, const bool right) {
	thrustOn = false;

	if (right) {
		angle += toRadians(360) * fElapsedTime;

	}
	if (left) {
		angle -= toRadians(360) * fElapsedTime;

	}
	if (isOnScreen) {
		if (on) {
			Vec2 acc = Vec2(cos(angle) * power, sin(angle) * power);
			vel += acc * fElapsedTime;
			thrustOn = true;
		}
		pos += vel * fElapsedTime;
		vel -= vel * .01;
	}
}

void Player::update(const ConsoleGraphicsEngine& temp) {

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
}

void Player::shoot() {
	if (shots.size() < maxShots && isOnScreen) {
		shots.push_back(Bullet(pos, Vec2(200 * cos(angle), 200 * sin(angle))));
		shots.at(shots.size() - 1).setColor(COLOR(BG_BLUE) + COLOR(FG_BLUE));
	}
}
void Player::shoot(const bool fire, const float fElapsedTime, const double delay) {
	timeFromShot += fElapsedTime;
	if (fire && timeFromShot > delay) {
		shoot();
		timeFromShot = 0;
	}
}
void Player::bulletHandler(const ConsoleGraphicsEngine& temp, const float fElapsedTime) {

	int countRemoved = 0;

	for (int i = 0; i < shots.size(); i++) {
		shots.at(i).update(temp, fElapsedTime);
		if (shots.at(i).timeLeft < 0) {
			shots.erase(shots.begin() + i - countRemoved);
			countRemoved++;

		}

	}
}
void Player::endBullet(int i) {
	shots.erase(shots.begin() + i);
}
void Player::drawShots(ConsoleGraphicsEngine temp) {
	for (int i = 0; i < shots.size(); i++) {
		shots.at(i).draw(temp);
	}
}
void Player::die() {
	isOnScreen = false;
	lives--;
}
bool Player::respawn(ConsoleGraphicsEngine temp, float fElapsedTime) {

	if (lives > 0 && !isOnScreen) {
		timeToRespawn += fElapsedTime;
		pos = Vec2(temp.width / 2, temp.height / 2);
		vel = Vec2(0, 0);
		int respawnTime = 2;
		if (timeToRespawn > respawnTime) {


			isOnScreen = true;
			timeToRespawn = 0;

		}
		// respawn radius (area that the bomb will cover)
		int rrW = 50;
		rr = (-abs(timeToRespawn - (respawnTime / 2.0)) / (respawnTime / 2.0) + 1) * (rrW - 10) + 10;
		temp.setColor(COLOR(FG_DARK_GREY) + COLOR(BG_DARK_GREY));
		Vec2 center = vecAvg(model);
		for (int i = 0; i < model.size() - 1; i++) {
			temp.drawLine(relPoint(model.at(i), center, angle) + pos, relPoint(model.at(i + 1), center, angle) + pos, '#');
		}
		temp.drawLine(relPoint(model.at(model.size() - 1), center, angle) + pos, relPoint(model.at(0), center, angle) + pos, '#');
		if (helper == 0) {
			helper = 1;
			temp.setColor(COLOR(FG_MAGENTA) + COLOR(BG_MAGENTA));
		}
		else {
			temp.setColor(COLOR(FG_BLUE) + COLOR(BG_BLUE));
			helper = 0;
		}
		for (int i = 0; i < 6; i++) {

			temp.drawLine(Vec2(temp.width / 2, temp.height / 2) + Vec2(rr * cos(toRadians(i * 360 / 6)), rr * sin(toRadians(i * 360 / 6))), Vec2(temp.width / 2, temp.height / 2) + Vec2(rr * cos(toRadians((i + 1) * 360 / 6)), rr * sin(toRadians((i + 1) * 360 / 6))), 'c');
			temp.drawLine(Vec2(temp.width / 2, temp.height / 2) + Vec2((rr - 10) * cos(toRadians(i * 360 / 6)), (rr - 10) * sin(toRadians(i * 360 / 6))), Vec2(temp.width / 2, temp.height / 2) + Vec2((rr - 10) * cos(toRadians((i + 1) * 360 / 6)), (rr - 10) * sin(toRadians((i + 1) * 360 / 6))), 'c');

		}
		return true;
	}
	return false;
}

void Player::draw(ConsoleGraphicsEngine temp) {
	if (isOnScreen) {
		if (thrustOn) {
			if (helper == 0) {
				temp.setColor(COLOR(BG_DARK_YELLOW) + COLOR(FG_DARK_YELLOW));
				helper = 1;
			}
			else {
				helper = 0;
				temp.setColor(COLOR(BG_RED) + COLOR(FG_RED));
			}

			temp.drawLine(pos + relPoint(Vec2(-2.5, -2), angle), pos + relPoint(Vec2(-6, 0), angle), '#');
			temp.drawLine(pos + relPoint(Vec2(-2.5, 2), angle), pos + relPoint(Vec2(-6, 0), angle), '#');
		}
		Entity::draw(temp);
	}
}
