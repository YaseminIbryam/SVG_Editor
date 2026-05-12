#pragma once
#include <string>

class Figure {
protected:
	std::string fill;
	std::string stroke;
	double strokeWidth;

public:
	Figure(std::string fill = "", std::string stroke = "", double strokeWidth = 0.0) : fill(fill), stroke(stroke), strokeWidth(strokeWidth) {}

	virtual ~Figure() {}

	virtual void print() const = 0;

	virtual void translate(double dx, double dy) = 0;

	virtual void withinRectangle(double x, double y, double width, double high) const = 0;

	virtual void withinCircle(double cx, double cy, double r) const = 0;
};