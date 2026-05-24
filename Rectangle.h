#pragma once
#include "Figure.h"
#include "Point.h"


/**
* @brief Клас за фигурата правоъгълник.
* Наследява базовия клас Figure и имплементира функциите за правоъгълник.
*/
class Rectangle : public Figure {
private:
	Point upperLeft;
	double width;
	double height;
public:
	Rectangle(Point upperLeft, double width, double height, std::string fill = "black", std::string stroke = "none", double strokeWidth = 1.0);

	/**
	* @brief Създава дълбоко копие на правоъгълника.
	* @return Circle* Указател към новосъздаденото копие на текущия правоъгълник.
	*/
	Rectangle* clone() const final;

	/// Извежда правоъгълника на екрана.
	void print() const final;

	/// Измества правоъгълника по двете оси спрямо текущото му местоположение.
	void translate(double horizontal, double vertical) final;

	/// Проверява дали правоъгълникът се съдържа изцяло в правоъгълен регион.
	bool withinRectangle(double x, double y, double width, double height) const final;

	/// Проверява дали фигурата се съдържа изцяло в кръгов регион.
	bool withinCircle(double cx, double cy, double r) const final;
};