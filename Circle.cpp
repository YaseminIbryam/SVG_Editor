#include <iostream>
#include <cmath>
#include "Circle.h"

Circle::Circle(Point center, double radious, std::string fill, std::string stroke, double strokeWidth)
	: center(center),
	radious(radious),
	Figure(fill, stroke, strokeWidth) {
};

Circle* Circle::clone() const {
	return new Circle(*this);
}

void Circle::print() const {
	std::cout << "circle " << center.x << ' ' << center.y << ' ' << radious << ' ' << fill;
	if (stroke != "none") {
		std::cout << ' ' << stroke << ' ' << strokeWidth;
	}
}

void Circle::translate(double horizontal, double vertical) {
	center.translate(horizontal, vertical);
}

bool Circle::withinRectangle(double x, double y, double width, double height) const {
	return (center.x - radious >= x) && (center.x + radious <= x + width) && (center.y - radious >= y) && (center.y + radious <= y + height);
}

bool Circle::withinCircle(double cx, double cy, double r) const {
	return center.withinCircle(cx, cy, r - radious);
}