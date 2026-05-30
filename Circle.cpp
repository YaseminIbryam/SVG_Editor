#include <iostream>
#include <cmath>
#include "Circle.h"

Circle::Circle(Point center, double radius, std::string fill, std::string stroke, double strokeWidth)
	: center(center),
	radius(radius),
	Figure(fill, stroke, strokeWidth) {
}

Circle* Circle::clone() const {
	return new Circle(*this);
}

void Circle::save(std::ostream& out) const {
	out << "<circle cx=\"" << center.x << "\" cy=\"" << center.y << "\" r=\"" << radius << "\" fill=\"" << fill << "\" ";
	if (stroke != "none") {
		out << "stroke=\"" << stroke << "\" ";
		if (std::abs(strokeWidth - 1.0) > 0.000001) {
			out << "stroke-width=\"" << strokeWidth << "\" ";
		}
	}
	out << "/>\n";
}

std::string Circle::getType() const {
	return "circle";
}

void Circle::print() const {
	std::cout << "circle " << center.x << ' ' << center.y << ' ' << radius << ' ' << fill;
	if (stroke != "none") {
		std::cout << ' ' << stroke << ' ' << strokeWidth;
	}
}

void Circle::translate(double horizontal, double vertical) {
	center.translate(horizontal, vertical);
}

bool Circle::withinRectangle(double x, double y, double width, double height) const {
	return (center.x - radius >= x) && (center.x + radius <= x + width) && (center.y - radius >= y) && (center.y + radius <= y + height);
}

bool Circle::withinCircle(double cx, double cy, double r) const {
	return center.withinCircle(cx, cy, r - radius);
}