#pragma once
#include "Entity.h"

class Asteroid : public Entity {

public:
	double life;
	int res;
	int splitMax;
	int splits;
	double rotationalVel;
	/*
	* construtor
	* 
	* @param pos1 : spawn position of asteriod
	* @param vel1 : velocity of asteriod
	* @param r : radius of asteriod
	* @param sMax : Splitmax, the number of times an asteriod will split
	* @param res1 : the resolution of the asteriod (how many lines in the mesh)
	*/
	Asteroid(Vec2 pos1, Vec2 vel1, double r, double sMax, int res1 = 20);
	
	/*
	* construtor
	*
	* @param pos1 : spawn position of asteriod
	* @param vel1 : velocity of asteriod
	* @param r : radius of asteriod
	* @param sMax : Splitmax, the number of times an asteriod will split
	* @param splitNum : how many times the asteriod has been split already
	* @param res1 : the resolution of the asteriod (how many lines in the mesh)
	*/
	Asteroid(Vec2 pos1, Vec2 vel1, double r, double sMax, double splitNum, int res1);
	
	/*
	* method to split asteriod
	* 
	* @return returns the resulting split asteriods in a vector
	*/
	vector<Asteroid> split();

	/*
	* updates the position of the asteriod
	*/
	void updatePos(ConsoleGraphicsEngine temp, float fElapsedTime);
};
