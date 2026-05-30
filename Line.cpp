#include <iostream>
#include "Line.h"
#include <cmath>

Line::Line(Point start, Point end, std::string stroke, double strokeWidth)
	: start(start),
	end(end),
	Figure("none", stroke, strokeWidth) {
}

Line* Line::clone() const {
	return new Line(*this);
}

void Line::save(std::ostream& out) const {
	out << "<line x1=\"" << start.x << "\" y1=\"" << start.y << "\" x2=\"" << end.x << "\" y2=\"" << end.y << "\" stroke=\"" << stroke << "\" ";
	if (std::abs(strokeWidth - 1.0) > 0.000001) {
		out << "stroke-width=\"" << strokeWidth << "\" ";
	}
	out << "/>\n";
}

std::string Line::getType() const {
	return "line";
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
}