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
	/**
	* @brief Конструктор за линия.
	* @param start Началната точка на линията.
	* @param end Крайната точка на линията.
	* @param stroke Цвят на контура на линията. Черен по подразбиране.
	* @param strokeWidth Дебелина на линията. По подразбиране е 1.0.
	*/
	Line(Point start, Point end, std::string stroke = "black", double strokeWidth = 1.0);

	/**
	* @brief Създава дълбоко копие на линията.
	* @return Line* Указател към новосъздаденото копие на текущата линия.
	*/
	Line* clone() const final;

	/**
	* @brief Записва линията в изходен поток във формат SVG.
	* @param out Изходният поток, в който ще се записват данните.
	*/
	void save(std::ostream& out) const final;

	/**
	 * @brief Връща типа на фигурата.
	 * @return std::string Низа на типа "line".
	 */
	std::string getType() const final;

	/// Извежда линията на екрана.
	void print() const final;

	/// Измества линията по двете оси спрямо текущото и местоположение.
	void translate(double horizontal, double vertical) final;

	/// Проверява дали линията се съдържа изцяло в правоъгълен регион.
	bool withinRectangle(double x, double y, double width, double height) const final;

	/// Проверява дали линията се съдържа изцяло в кръгов регион.
	bool withinCircle(double cx, double cy, double r) const final;
};