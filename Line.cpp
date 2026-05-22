#include <iostream>
#include "Line.h"

Line::Line(Point start, Point end, std::string fill, std::string stroke, double strokeWidth)
	: start(start),
	end(end),
	Figure(fill, stroke, strokeWidth) {
};

void Line::print() const {

}

void Line::translate(double dx, double dy) {

}

bool Line::withinRectangle(double x, double y, double width, double high) const {

}

bool Line::withinCircle(double cx, double cy, double r) const {

};