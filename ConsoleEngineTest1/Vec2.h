#pragma once
#include <iostream>
#include <vector>
/* 
* class for storing 2 dimensional vectors and doing operations with them
*/

class Vec2 {

public:
	double x;
	double y;

	/* 
	* constructor that takes in two values for x and y
	* 
	* @param x1 : the x value of the vector
	* @param y1 : the y value of the vector
	*/
	Vec2(double x1, double y1);

	/*
	* default vector constructior (initializes x and y to 0)
	*/
	Vec2();

	/*
	* returns magnitude (length) of the vector
	* 
	* @return This method returns the length of a given vector
	*/
	double getMagnitude();

	/*
	* Overloads the add operator for the vector class
	* 
	* @return the add operation returns a new vector in the form of (a.x+b.x, a.y+b.y)
	*/
	Vec2 operator+(const Vec2& b);

	/*
	* Overloads the subtract operator for the vector class
	*
	* @return the subtract operation returns a new vector in the form of (a.x-b.x, a.y-b.y)
	*/
	Vec2 operator-(const Vec2& b);

	/*
	* scalar multiply
	*
	* @return the times operation returns a new vector in the form of (a.x*b, a.y*b)
	*/
	Vec2 operator*(const double b);

	/*
	* scalar divide
	*
	* @return the divide operation returns a new vector in the form of (a.x/b, a.y/b)
	*/
	Vec2 operator/(const double b);
	void operator+=(const Vec2& b);
	void operator-=(const Vec2& b);
	void operator*=(const double b);
	void operator/=(const double b);


};
/*
* revolves point around origin based on a radian angle
*/
Vec2 relPoint(double x1, double y1, double angle);

/*
* supposed to rotate point around another point
* but I dropped the ball and now when I fix it to do
* what I actually want it to do, my game breaks so
* its going to stay
*/
Vec2 relPoint(double x1, double y1, double xC, double yC, double angle);
Vec2 relPoint(Vec2 point, double angle);
Vec2 relPoint(Vec2 point, Vec2 center, double angle);

/*
* averages all vectors in a list of vectors (returns centerpoint)
*/
Vec2 vecAvg(std::vector<Vec2> temp);

/*
* converts degrees to radians 
*/
double toRadians(double degrees);

