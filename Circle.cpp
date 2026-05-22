#include <iostream>
#include "Circle.h"

Circle::Circle(Point center, double radious, std::string fill, std::string stroke, double strokeWidth)
	: center(center),
	radious(radious),
	Figure(fill, stroke, strokeWidth) {
};

void Circle::print() const {

}

void Circle::translate(double dx, double dy) {

}

bool Circle::withinRectangle(double x, double y, double width, double high) const {

}

bool Circle::withinCircle(double cx, double cy, double r) const {

};