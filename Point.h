#pragma once

#include <cmath>


/**
* @brief Структура Point за представяне на точка в равнината
*/
struct Point {
	double x; ///< Абсциса
	double y; ///< Ордината

	/// Конструктор по подразбиране
	Point() = default;

	/**
	* @brief Конструктор за точка
	* @param x Стойност за абсцисата
	* @param y Стойност за ординатата
	*/
	Point(double x, double y) : x(x), y(y) {}

	/**
	* @brief Проверява дали точката се намира вътре в даден правоъгълник или по контура му.
	* @param rectX X координата на горния ляв ъгъл на правоъгълника.
	* @param rectY Y координата на горния ляв ъгъл на правоъгълника.
	* @param width Ширина на правоъгълника.
	* @param height Височина на правоъгълника.
	* @return true Ако точката е в правоъгълника.
	* @return false Ако точката е извън правоъгълника.
	*/
	bool withinRectangle(double rectX, double rectY, double width, double height) const {
		return ((x <= rectX + width) && (x >= rectX) && (y <= rectY + height) && (y >= rectY));
	}
	
	/**
	* @brief Проверява дали точката се намира вътре в даден кръг или по контура му.
	* @param cx X координата на центъра на кръга.
	* @param cy Y координата на центъра на кръга.
	* @param r Радиус на кръга.
	* @return true Ако точката е в кръга.
	* @return false Ако точката е извън кръга.
	*/
	bool withinCircle(double cx, double cy, double r) const {
		return (std::sqrt((cx - x) * (cx - x) + (cy - y) * (cy - y)) <= r);
	}

	/**
	* @brief Измества точката по двете оси спрямо текущото и местоположение.
	* @param horizontal Промяна по абсцисата. Положителна стойност мести надясно, отрицателна - наляво.
	* @param vertical Промяна по ординатата. Положителна стойност мести надолу, отрицателна - нагоре.
	*/
	void translate(double horizontal, double vertical) {
		x += horizontal;
		y += vertical;
	}
};