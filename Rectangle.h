#pragma once
#include "Figure.h"
#include "Point.h"

class Rectangle : public Figure {
private:
	Point UpperLeft;
	double width;
	double hight;
public:
	Rectangle(Point UpperLeft, double width, double hight, std::string fill, std::string stroke, double strokeWidth);

	void print() const final;

	void translate(double dx, double dy) final;

	void withinRectangle(double x, double y, double width, double high) const final;

	void withinCircle(double cx, double cy, double r) const final;
};