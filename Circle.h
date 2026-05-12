#pragma once
#include "Figure.h"
#include "Point.h"

class Circle : public Figure {
private:
	Point center;
	double radious;
public:
	Circle(Point center, double radious, std::string fill, std::string stroke, double strokeWidth);
	
	void print() const final;

	void translate(double dx, double dy) final;

	void withinRectangle(double x, double y, double width, double high) const final;

	void withinCircle(double cx, double cy, double r) const final;
};