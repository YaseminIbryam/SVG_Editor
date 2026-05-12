#pragma once
#include "Figure.h"
#include "Point.h"

class Line : public Figure {
private:
	Point start;
	Point end;
public:
	Line(Point start, Point end, std::string fill, std::string stroke, double strokeWidth);

	void print() const final;

	void translate(double dx, double dy) final;

	void withinRectangle(double x, double y, double width, double high) const final;

	void withinCircle(double cx, double cy, double r) const final;
};