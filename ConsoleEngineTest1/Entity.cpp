#include "Entity.h"

Entity::Entity(const Vec2& pos1, const Vec2& vel1, const double angle1, const double r1) {
	pos = pos1;
	vel = vel1;
	angle = angle1;
	color = COLOR(FG_WHITE) + COLOR(BG_WHITE);
	radius = r1;
}

void Entity::draw(ConsoleGraphicsEngine& con) const {

	Vec2 center = vecAvg(model);

	con.setColor(color);
	for (int i = 0; i < model.size() - 1; i++) {
		con.drawLine(relPoint(model.at(i), center, angle) + pos, relPoint(model.at(i + 1), center, angle) + pos, '#');
	}
	con.drawLine(relPoint(model.at(model.size() - 1), center, angle) + pos, relPoint(model.at(0), center, angle) + pos, '#');

}

void Entity::setColor(const int nextColor) {
	color = nextColor;
}