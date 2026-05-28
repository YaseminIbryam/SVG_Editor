#include <iostream>
#include "Rectangle.h"


Rectangle::Rectangle(Point upperLeft, double width, double height, std::string fill, std::string stroke, double strokeWidth)
	: upperLeft(upperLeft),
	width(width),
	height(height),
	Figure(fill, stroke, strokeWidth) {
}

Rectangle* Rectangle::clone() const {
	return new Rectangle(*this);
}

void Rectangle::save(std::ostream& out) const {
	out << "<rect x=\"" << upperLeft.x << "\" y=\"" << upperLeft.y << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\"" << fill << "\" ";
	if (stroke != "none") {
		out << "stroke=\"" << stroke << "\" ";
		if (strokeWidth != 1) {
			out << "stroke-width=\"" << strokeWidth << "\" ";
		}
	}
	out << "/>\n";
}

void Rectangle::print() const {
	std::cout << "rectangle " << upperLeft.x << ' ' << upperLeft.y << ' ' << width << ' ' << height << ' ' << fill;
	if (stroke != "none") {
		std::cout << ' ' << stroke << ' ' << strokeWidth;
	}
}

void Rectangle::translate(double horizontal, double vertical) {
	upperLeft.translate(horizontal, vertical);
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