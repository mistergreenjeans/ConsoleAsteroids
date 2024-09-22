#pragma once

#include <vector>
#include "ConsoleGraphicsEngine.h"
#include "Vec2.h"

/*
* Class that stores a position, velocity, angle, and radius 
* (traits that every object in the game will have)
*/
class Entity {
public:
	int color;
	Vec2 pos;
	Vec2 vel;
	double angle;
	double radius;
	std::vector<Vec2> model;

	/*
	* Constructor
	* 
	* @param pos1 : x,y position that Entity will be at
	* @param vel1 : Velocity that Entity will start at
	* @param angle1 : the angle that the entity will spawn at
	* @param r1 : the radius of the Entity
	*/
	Entity(const Vec2& pos1, const Vec2& vel1, const double angle1, const double r1);

	/*
	* this method will draw the Entity based on its (2D) wireframe model
	* 
	* @param con : the console engine
	*/
	void draw(ConsoleGraphicsEngine& con) const;

	/*
	* this method changes the color that the entity will be drawn as
	* 
	* @param nextColor : The color that the entity will change to
	*/
	void setColor(const int nextColor);

};