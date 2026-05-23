#pragma once
#include "Figure.h"
#include "Point.h"

/**
* @brief Клас за фигурата кръг.
* Наследява базовия клас Figure и имплементира функциите за кръг.
*/
class Circle : public Figure {
private:
	Point center; ///< Точка на центъра на кръга
	double radious; ///< Дължина на радиуса на кръга
public:
	/** 
	* @brief Конструктор за създаване на кръг.
	* @param center Център
	* @param radious Радиус
	* @param fill Цвят на пълнежа
	* @param stroke Цвят на контрура
	* @param strokeWidth Дебелина на контура
	*/
	Circle(Point center, double radious, std::string fill = "black", std::string stroke = "none", double strokeWidth = 1.0);
	
	/// Извежда кръга на екрана.
	void print() const final;

	/// Измества кръга спрямо текущото му местоположение.
	void translate(double dx, double dy) final;

	/// Проверява дали кръгът се съдържа изцяло в правоъгълен регион.
	bool withinRectangle(double x, double y, double width, double height) const final;

	/// Проверява дали кръгът се съдържа изцяло в кръгов регион.
	bool withinCircle(double cx, double cy, double r) const final;
};