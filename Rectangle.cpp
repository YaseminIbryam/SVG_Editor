#include <iostream>
#include "Rectangle.h"


Rectangle::Rectangle(Point UpperLeft, double width, double hight, std::string fill, std::string stroke, double strokeWidth)
	: UpperLeft(UpperLeft),
	width(width),
	hight(hight),
	Figure(fill, stroke, strokeWidth) {
};


void Rectangle::print() const {

}

void Rectangle::translate(double dx, double dy) {

}

bool Rectangle::withinRectangle(double x, double y, double width, double high) const {

}

bool Rectangle::withinCircle(double cx, double cy, double r) const {

};