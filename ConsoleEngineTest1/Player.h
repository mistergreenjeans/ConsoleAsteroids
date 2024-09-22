#pragma once
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity {
public:
	vector<Bullet> shots;
	int maxShots = 5;
	int lives;
	bool isOnScreen;
	double timeToRespawn = 0;
	double timeFromShot = 0;
	int helper;
	bool thrustOn;
	double rr = 0;
	/*
	* constructor for player object
	*/
	Player(const ConsoleGraphicsEngine& temp);

	/*
	* manages players movement
	* 
	* @param power : rate of acceleration
	* @param fElapsedTime : delta time
	* @param on : is player holding the forward key
	* @param left : is the player holding the left key
	* @param right : is the player holding the right key
	*/
	void thrust(const double power, const float fElapsedTime,
				const bool on, const bool left, const bool right);

	/*
	* makes the player wrap across the screen
	*/
	void update(const ConsoleGraphicsEngine& temp);

	/*
	* makes the player fire a bullet
	*/
	void shoot();

	/*
	* handles the firing of bullets from the player
	* 
	* @param fire : is the player firing
	* @param fElapsedTime : delta time
	* @param delay : how much time between shots firing
	*/
	void shoot(const bool fire, const float fElapsedTime, const double delay);

	/*
	* updates bullets and removes bullets from list after they expire
	*/
	void bulletHandler(const ConsoleGraphicsEngine& temp, const float fElapsedTime);
	
	/*
	* removes bullet from list
	*/
	void endBullet(int i);

	/*
	* draw bullets in list
	*/
	void drawShots(ConsoleGraphicsEngine temp);

	/*
	* function called when player gets hit
	* handles lives and disabling the player until the respawn
	*/
	void die();

	/*
	* respawns the player and creates a saftey radius for them so they
	* dont die again before they can move
	*/
	bool respawn(ConsoleGraphicsEngine temp, float fElapsedTime);

	/*
	* draw the player
	*/
	void draw(ConsoleGraphicsEngine temp);
};