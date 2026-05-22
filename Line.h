#pragma once
#include "Figure.h"
#include "Point.h"


/**
* @brief Клас за фигурата Линия.
* Наследява базовия клас Figure и имплементира функциите за линия.
*/
class Line : public Figure {
private:
	Point start; ///< Начална точка на линията
	Point end; ///< Крайна точка на линията
public:
	Line(Point start, Point end, std::string fill = "none", std::string stroke = "black", double strokeWidth = 1.0);

	/// Извежда линията на екрана.
	void print() const final;

	/// Измества линията по двете оси спрямо текущото и местоположение.
	void translate(double dx, double dy) final;

	/// Проверява дали линията се съдържа изцяло в правоъгълен регион.
	bool withinRectangle(double x, double y, double width, double high) const final;

	/// Проверява дали линията се съдържа изцяло в кръгов регион.
	bool withinCircle(double cx, double cy, double r) const final;
};