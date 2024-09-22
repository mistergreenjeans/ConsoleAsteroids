#pragma once
#include "Entity.h"

class Bullet : public Entity {
public:
	double timeLeft;
	/*
	* constructor
	* @param pos1 : the spawn position of the bullet
	* @param vel1 : the velocity of the bullet
	*/
	Bullet(Vec2 pos1, Vec2 vel1);

	/*
	* updates the position based on the velocity of the bullet
	* as well as manages screen wrapping
	*/
	void update(ConsoleGraphicsEngine temp, float fElapsedTime);
};
