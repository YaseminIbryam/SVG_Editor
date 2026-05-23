#pragma once

#include <cmath>


/**
* @brief Структура Point за представяне на точка с абсциса x и ординатата y
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
	* @brief Проверява дали точката е в правоъгълник или част от него
	* @return false Ако точката е извън правоъгълника
	* @return true Ако точката е в провоъгълника
	*/
	bool withinRectangle(double rectX, double rectY, double width, double height) const {
		return ((x <= rectX + width) && (x >= rectX) && (y <= rectY + height) && (y >= rectY));
	}
	
	/**
	* @brief Проверява дали точката е в кръг или част от него
	* @return true Ако точката е в кръга
	* @return false Ако точката е извън кръга
	*/
	bool withinCircle(double cx, double cy, double r) const {
		return (std::sqrt((cx - x) * (cx - x) + (cy - y) * (cy - y)) <= r);
	}

	/**
	* @brief Измества точката по двете оси спрямо текущото и местоположение.
	* @param dx Делта X. Промяна по абсциса. Положителна стойност мести надясно, отрицателна - наляво.
	* @param dy Делта Y. Промяна по ордината. Положителна стойност мести надолу, отрицателна - нагоре.
	*/
	void translate(double dx, double dy) {
		x += dx;
		y += dy;
	}


};