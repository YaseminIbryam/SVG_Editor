#include <iostream>
#include "Line.h"

Line::Line(Point start, Point end, std::string stroke, double strokeWidth)
	: start(start),
	end(end),
	Figure("none", stroke, strokeWidth) {
};

Line* Line::clone() const {
	return new Line(*this);
}

void Line::print() const {
	std::cout << "line " << start.x << ' ' << start.y << ' ' << end.x << ' ' << end.y << ' ' << stroke << ' ' << strokeWidth;
}

void Line::translate(double horizontal, double vertical) {
	start.translate(horizontal, vertical);
	end.translate(horizontal, vertical);
}

bool Line::withinRectangle(double x, double y, double width, double height) const {
	return ((start.withinRectangle(x, y, width, height) && end.withinRectangle(x, y, width, height)));
}

bool Line::withinCircle(double cx, double cy, double r) const {
	return ((start.withinCircle(cx, cy, r) && end.withinCircle(cx, cy, r)));
};