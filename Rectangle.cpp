#include <iostream>
#include "Rectangle.h"


Rectangle::Rectangle(Point upperLeft, double width, double height, std::string fill, std::string stroke, double strokeWidth)
	: upperLeft(upperLeft),
	width(width),
	height(height),
	Figure(fill, stroke, strokeWidth) {
}


void Rectangle::print() const {
	std::cout << "rectangle " << upperLeft.x << ' ' << upperLeft.y << ' ' << width << ' ' << height << ' ' << fill;
	if (stroke != "none") {
		std::cout << ' ' << stroke << ' ' << strokeWidth;
	}
	std::cout << std::endl;
}

void Rectangle::translate(double dx, double dy) {
	upperLeft.translate(dx, dy);
}

bool Rectangle::withinRectangle(double x, double y, double width, double height) const {
	return (upperLeft.withinRectangle(x, y, width, height) && (upperLeft.x + this->width <= x + width) && (upperLeft.y + this->height <= y + height));
}

bool Rectangle::withinCircle(double cx, double cy, double r) const {
	Point upperRight(upperLeft.x + this->width, upperLeft.y);
	Point bottomLeft(upperLeft.x, upperLeft.y + this->height);
	Point bottomRight(upperRight.x, bottomLeft.y);
	return (upperLeft.withinCircle(cx, cy, r) && upperRight.withinCircle(cx, cy, r) && bottomLeft.withinCircle(cx, cy, r) && bottomRight.withinCircle(cx, cy, r));
}