#include "Vec2.h"
Vec2::Vec2(double x1, double y1) {
	x = x1;
	y = y1;
}

Vec2::Vec2() {
	x = 0;
	y = 0;
}

double Vec2::getMagnitude() {
	return sqrt(x * x + y * y);
}

Vec2 Vec2::operator+(const Vec2& b) {
	return Vec2(x + b.x, y + b.y);
}

Vec2 Vec2::operator-(const Vec2& b) {
	return Vec2(x - b.x, y - b.y);
}

Vec2 Vec2::operator*(const double b) {
	return Vec2(x * b, y * b);
}

Vec2 Vec2::operator/(const double b) {
	return Vec2(x / b, y / b);
}

void Vec2::operator+=(const Vec2& b) {
	x += b.x;
	y += b.y;
}

void Vec2::operator-=(const Vec2& b) {
	x -= b.x;
	y -= b.y;
}

void Vec2::operator*=(const double b) {
	x *= b;
	y *= b;
}

void Vec2::operator/=(const double b) {
	x /= b;
	y /= b;
}

Vec2 vecAvg(std::vector<Vec2> temp) {
	Vec2 result(0, 0);
	for (int i = 0; i < temp.size(); i++) {
		result += temp.at(i);
	}
	result /= temp.size();
	return result;
}

Vec2 relPoint(double x1, double y1, double angle) {
	//double magnitude = sqrt(x1 * x1 + y1 * y1);
	//double relAngle = atan2(y1,x1);

	//return Vec2(magnitude * cos(angle + relAngle), magnitude * sin(angle + relAngle));
	return Vec2(x1 * cos(angle) - y1 * sin(angle), x1 * sin(angle) + y1 * cos(angle));
}
Vec2 relPoint(double x1, double y1, double xC, double yC, double angle) {
	double magnitude = sqrt((xC - x1) * (xC - x1) + (yC - y1) * (yC - y1));
	double relAngle = atan2(-yC + y1, -xC + x1);

	//accident that works so its not going away for this project :(
	return Vec2(magnitude * cos(angle + relAngle), magnitude * sin(angle + relAngle));

	//x1 - xC;
	//y1 - yC;
	//return Vec2(x1 * cos(angle) - y1 * sin(angle), x1 * sin(angle) + y1 * cos(angle)) + Vec2(xC, yC);
}
Vec2 relPoint(Vec2 point, double angle) {
	return relPoint(point.x, point.y, angle);
}
Vec2 relPoint(Vec2 point, Vec2 center, double angle) {
	return relPoint(point.x, point.y, center.x, center.y, angle);
}

double toRadians(double degrees) {
	return (degrees / 180) * 3.141592;
}